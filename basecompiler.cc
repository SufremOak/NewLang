#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <regex>
#include <memory>

class BaseCompiler {
public:
    BaseCompiler() : context(), builder(context), module(new llvm::Module("NewLangModule", context)) {
        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmPrinter();
        llvm::InitializeNativeTargetAsmParser();
    }

    void compile(const std::string &sourceCode) {
        auto tokens = lex(sourceCode);
        auto ast = parse(tokens);
        generateCode(ast);
    }

    void printIR() {
        module->print(llvm::outs(), nullptr);
    }

    void execute() {
        std::string errStr;
        std::unique_ptr<llvm::Module> mod(module.release());
        llvm::ExecutionEngine *engine = llvm::EngineBuilder(std::move(mod)).setErrorStr(&errStr).create();
        if (!engine) {
            llvm::errs() << "Failed to create ExecutionEngine: " << errStr << "\n";
            return;
        }

        llvm::Function *mainFunc = engine->FindFunctionNamed("Main");
        if (!mainFunc) {
            llvm::errs() << "Function 'Main' not found in module.\n";
            return;
        }

        engine->finalizeObject();
        std::vector<std::string> emptyArgs;
        engine->runFunctionAsMain(mainFunc, emptyArgs, nullptr);
    }

private:
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder;
    std::unique_ptr<llvm::Module> module;

    struct Token {
        enum Type { Keyword, Identifier, Symbol, String, Number, EndOfFile, Comment } type;
        std::string value;
    };

    struct ASTNode {
        enum Type { Function, Call, StringLiteral, NumberLiteral, VariableDeclaration, Block } type;
        std::string value;
        std::vector<ASTNode> children;
    };

    std::vector<Token> lex(const std::string &sourceCode) {
        std::vector<Token> tokens;
        std::regex tokenPatterns(R"((req|func|exit|inv|as|Stage|io\.println\*ascii|fs\.scanFilesystem|fs\.createVariable|for|do|on|Main|\(|\)|\{|\}|\"[^\"]*\"|\d+|\w+|\s+|//[^\n]*|.))");
        auto words_begin = std::sregex_iterator(sourceCode.begin(), sourceCode.end(), tokenPatterns);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;
            std::string match_str = match.str();
            if (match_str == " " || match_str == "\n" || match_str == "\t") continue; // Skip whitespace
            Token token;
            if (match_str == "req" || match_str == "func" || match_str == "exit" || match_str == "inv" || match_str == "as" || match_str == "Stage") {
                token.type = Token::Keyword;
            } else if (match_str == "(" || match_str == ")" || match_str == "{" || match_str == "}") {
                token.type = Token::Symbol;
            } else if (match_str[0] == '"') {
                token.type = Token::String;
            } else if (std::isdigit(match_str[0])) {
                token.type = Token::Number;
            } else if (match_str.substr(0, 2) == "//") {
                token.type = Token::Comment;
            } else {
                token.type = Token::Identifier;
            }
            token.value = match_str;
            tokens.push_back(token);
        }
        tokens.push_back({Token::EndOfFile, ""});
        return tokens;
    }

    ASTNode parse(const std::vector<Token> &tokens) {
        // Simple parser for demonstration purposes
        ASTNode root;
        root.type = ASTNode::Function;
        root.value = "Main";
        for (const auto &token : tokens) {
            if (token.type == Token::String) {
                ASTNode node;
                node.type = ASTNode::StringLiteral;
                node.value = token.value;
                root.children.push_back(node);
            }
        }
        return root;
    }

    void generateCode(const ASTNode &ast) {
        llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getVoidTy(), false);
        llvm::Function *function = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, ast.value, module.get());

        llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entry", function);
        builder.SetInsertPoint(entry);

        llvm::FunctionType *printfType = llvm::FunctionType::get(builder.getInt32Ty(), builder.getInt8PtrTy(), true);
        llvm::Function *printfFunc = llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf", module.get());

        llvm::FunctionType *exitType = llvm::FunctionType::get(builder.getVoidTy(), builder.getInt32Ty(), false);
        llvm::Function *exitFunc = llvm::Function::Create(exitType, llvm::Function::ExternalLinkage, "exit", module.get());

        for (const auto &child : ast.children) {
            if (child.type == ASTNode::StringLiteral) {
                llvm::Value *formatStr = builder.CreateGlobalStringPtr(child.value);
                builder.CreateCall(printfFunc, formatStr);
            }
        }

        builder.CreateCall(exitFunc, builder.getInt32(0));
        builder.CreateRetVoid();

        llvm::verifyFunction(*function);
    }
};

int main() {
    BaseCompiler compiler;
    std::string helloWorldCode = R"(
        req io;
        func Main() {
            io.println*ascii("Hello, World!\n");
            exit(0);
        }
        inv(func(Main)) as Stage();
    )";
    compiler.compile(helloWorldCode);
    compiler.printIR();
    compiler.execute();

    std::string listFilesCode = R"(
        req io;
        req fs;
        func Main() {
            fs.scanFilesystem(".") * NL.Create.action({
                on fs.scanFilesystem do [
                    fs.createVariable(for fs.Files('files'))
                    io.println*ascii(files)
                ]
            })
            exit(0);
        }
        inv(func(Main)) as Stage(fs());
    )";
    compiler.compile(listFilesCode);
    compiler.printIR();
    compiler.execute();

    return 0;
}