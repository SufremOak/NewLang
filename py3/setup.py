from setuptools import setup
from Cython.build import cythonize

setup(
        ext_module=(['toolkit.pyx']).cythonize()
)
