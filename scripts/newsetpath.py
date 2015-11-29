from subprocess import call
import string
setpath_template = """@echo off
set PATH=%PATH%;${dirs}
echo Sciezki zostaly zaaktualizowane!
"""

def MakeNewPathFile(libs):
    with open('after_install.bat', 'w') as f:
        f.write(string.Template(setpath_template).substitute(dirs=';'.join(libs)))
