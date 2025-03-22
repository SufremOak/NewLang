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

class BaseCompiler {
public:
    BaseCompiler() : context(), builder(context), module("NewLangModule", context) {
        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmPrinter();
        llvm::InitializeNativeTargetAsmParser();
    }

    void compile() {
        // Example function: void Main() { printf("Hello, World!\n"); exit(0); }
        llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getVoidTy(), false);
        llvm::Function *function = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "Main", module);

        llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entry", function);
        builder.SetInsertPoint(entry);

        // Create printf function
        llvm::FunctionType *printfType = llvm::FunctionType::get(builder.getInt32Ty(), builder.getInt8PtrTy(), true);
        llvm::Function *printfFunc = llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf", module);

        // Create exit function
        llvm::FunctionType *exitType = llvm::FunctionType::get(builder.getVoidTy(), builder.getInt32Ty(), false);
        llvm::Function *exitFunc = llvm::Function::Create(exitType, llvm::Function::ExternalLinkage, "exit", module);

        // Create format string
        llvm::Value *formatStr = builder.CreateGlobalStringPtr("Hello, World!\n");

        // Call printf
        builder.CreateCall(printfFunc, formatStr);

        // Call exit(0)
        builder.CreateCall(exitFunc, builder.getInt32(0));

        builder.CreateRetVoid();

        llvm::verifyFunction(*function);
    }

    void printIR() {
        module.print(llvm::outs(), nullptr);
    }

    void execute() {
        std::string errStr;
        llvm::ExecutionEngine *engine = llvm::EngineBuilder(std::unique_ptr<llvm::Module>(&module)).setErrorStr(&errStr).create();
        if (!engine) {
            llvm::errs() << "Failed to create ExecutionEngine: " << errStr << "\n";
            return;
        }

        llvm::Function *mainFunc = module.getFunction("Main");
        if (!mainFunc) {
            llvm::errs() << "Function 'Main' not found in module.\n";
            return;
        }

        engine->finalizeObject();
        engine->runFunctionAsMain(mainFunc, {}, nullptr);
    }

private:
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder;
    llvm::Module module;
};

int main() {
    BaseCompiler compiler;
    compiler.compile();
    compiler.printIR();
    compiler.execute();
    return 0;
}