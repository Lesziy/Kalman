import platform, os, glob
from scripts.newsetpath import MakeNewPathFile
from subprocess import call

#Drogi uzytkowniku ktory zajrzales tutaj ze wzgledu na bledy dot. brak bibliotek,
#To jest miejsce dla ciebie:
include_dirs = {
    'windows':
    {
        'boost' : "C:\Boost",
        'SDL' : "C:\\Program Files (x86)\\SDL\include",
        'python' : "C:\Python27\include",
        'wx' : "C:\wxWidgets-3.0.2\include",
        'wxmsvc' : "C:\wxWidgets-3.0.2\include\msvc"
    },
    'linux':
    {
        'python' : '/usr/include/python2.7',
        'SDL': '/usr/include/SDL2',
    }
}

libs_dirs = {
    'windows':
    {
        'python': 'C:\Python27\libs',
        'SDL': 'C:\\Program Files (x86)\\SDL\lib\\x64',
        'wx': 'C:\wxWidgets-3.0.2\lib\\vc_x64_lib',
        'boost': 'C:\Boost\lib64-msvc-14.0'
    },
    'linux':
    {
        'python': '/usr/lib64/python2.7'
        #'/usr/lib64'
    }
}

external_libs = {
    'windows' : ['SDL2', "python27", "legacy_stdio_definitions", "SDL2main"],
    'linux' : ['SDL2', "python2.7", "boost_python", "GL"]
}

libs = ["Generator", "SimpleSDL", "wxGUI"]



program_sources = ['src/Main.cpp']
libs_sources = map(lambda x: glob.glob('src/' + x + '/*.cpp'), libs)
test_sources = Glob('test/*.cpp')
examples_sources = glob.glob('examples/*.cpp')

include_search_path = ['include'] + map(lambda x: 'src/' + x, libs)

app = []
apptest = []
examples = []
libs_shared = []

env = Environment(CPPPATH=include_search_path,LIBPATH=['.'])

env['SYSTEM'] = platform.system().lower()
env.Append(CPPPATH=include_dirs[env['SYSTEM']].values())
env.Append(LIBPATH=libs_dirs[env['SYSTEM']].values())

if env['SYSTEM'] == 'windows':
    env.Append( CXXFLAGS='/EHsc /MD /D _UNICODE /D WIN32 /D WINVER=0x0400 /D __WXMSW__ /D _WINDOWS', LINKFLAGS='/SUBSYSTEM:CONSOLE' )



elif env['SYSTEM'] == 'linux':
    env.ParseConfig("wx-config --cxxflags --libs --gl-libs")
    env.Append(CXXFLAGS="-std=c++0x")

    #Aby aplikacja widziala biblioteki wspodzielone w folderze aplikacji
    env.Append( LINKFLAGS = Split('-z origin'), RPATH = env.Literal(os.path.join('\\$$ORIGIN')) )



#
# Konfiguracja
#
conf = Configure(env)

if not conf.CheckCXXHeader('boost/test/included/unit_test.hpp'):
    print 'Boost.Test not found!'
    Exit(1)

if not conf.CheckCXXHeader('pyconfig.h'):
    print 'Python development files not found - fix paths in SConscript file or install them'
    Exit(1)


if not conf.CheckCHeader('SDL.h'):
    print 'SDL2.h not found - install it or fix path in Sconscript file'
    Exit(1)

if not conf.CheckLib('SDL2'):
    print 'SDL2 lib not found, exiting!'
    Exit(1)

if not conf.CheckLib('SDL2main') and env['SYSTEM']=='windows':
    print 'SDL2main lib not found, exiting!'
    Exit(1)

if not conf.CheckCXXHeader('boost/python.hpp'):
    print 'Boost.Python not found!'
    Exit(1)

env = conf.Finish()

#
# Kompilacja.
#


for i in range(len(libs)):
    libs_shared += env.Library(libs[i], libs_sources[i], LIBS=external_libs[env['SYSTEM']])
testEnv = env.Clone()

#
# Targety
#

#Domyslny
app = env.Program("app", program_sources, LIBS=libs_shared+external_libs[env['SYSTEM']]+env['LIBS'])
env.Depends(app, libs_shared)

Default(app)

#Testy
for i in range(len(libs)):
    apptest += testEnv.Program("test-" +libs[i]  , 'test/test_'+libs[i]+'.cpp', LIBS=external_libs[env['SYSTEM']]+libs)

#Przyklady
for j in examples_sources:
    examples += testEnv.Program(os.path.splitext(os.path.split(j)[1])[0],j, LIBS=external_libs[env['SYSTEM']]+libs)

Alias('test', apptest)
Alias('examples', examples)

#all
Alias('all', app)
Alias('all', apptest)
Alias('all', examples)

if env['SYSTEM'] == 'windows':
    MakeNewPathFile(libs_dirs[env['SYSTEM']].values())
    print 'W przypadku szczesliwej kompilacji uruchom after_install.bat'
