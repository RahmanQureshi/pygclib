from distutils.core import setup, Extension
import os

module1 = Extension('gclib',
                    sources = ['source/gclibmodule.c'],
                    include_dirs = ['./include'],
                    libraries = ['lib/gclib', 'lib/gclibo'])

setup (name = 'gclib',
       version = '1.0',
       description = 'Control galil motion controllers using python',
       ext_modules = [module1],
       package_dir = {
       	'':'source'
       },
       #package_data = {'':['source/dll/*.dll']},
       data_files = [('', ['source/dll/gclib.dll','source/dll/gclibo.dll'])],
       py_modules = ['pygclib'])