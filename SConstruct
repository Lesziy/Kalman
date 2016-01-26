import platform, os, glob
from scripts.newsetpath import MakeNewPathFile
from subprocess import call

#Drogi uzytkowniku ktory zajrzales tutaj ze wzgledu na bledy dot. brak bibliotek,
#To jest miejsce dla ciebie:
include_dirs = {
    'windows':
    {
        'jp_boost' : "C:\\Boost2",
        'jp_python' : "C:\\Python27\\include",
        'ps_boost' : "D:\\deps\\Boost",
        'ps_python' : "D:\\deps\Python27\include",
		'mb_boost' :  "C:\\local\\boost_1_59_0",
		'mb_python' : "C:\\Python27\\include"
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
        'jp_python': 'C:\\Python27\\libs',
        'jp_boost': 'C:\\boost2\\lib64-msvc-14.0',
        'ps_python': 'D:\\deps\Python27\libs',
        'ps_boost': 'D:\\deps\Boost\lib64-msvc-14.0',
        'mb_python': 'C:\\Python27\\libs',
        'mb_boost': 'C:\\local\\boost_1_59_0\\lib64-msvc-14.0'
    },
    'linux':
    {
        'python': '/usr/lib64/python2.7',
        'libs': '/usr/lib'
    }
}


external_libs = {
    'windows': ["python27"],
    'linux': ["python2.7", "boost_system", "boost_filesystem","boost_program_options","boost_python","pthread","boost_log_setup","boost_log", "boost_iostreams"]
}

libs = ["Common","Generator", "KalmanFilter","Writer", "Sensors"]

doxygen_builder = Builder(action = 'doxygen')

include_search_path = ['#include'] + map(lambda x: '#src/' + x, libs)

app = []
apptest = []
examples = []
libs_shared = []

env = Environment(CPPPATH=include_search_path)

env['SYSTEM'] = platform.system().lower()
env.Append( CPPPATH=include_dirs[env['SYSTEM']].values(), LIBPATH=libs_dirs[env['SYSTEM']].values(),
            BUILDERS={'Docs':doxygen_builder})
env['ENV']['PATH']+=os.environ['PATH']
env['EXTERNAL_LIBS'] = external_libs[env['SYSTEM']]
env['SHARED_LIBS'] = []
Progress(['-\r', '\\\r', '|\r', '/\r'], interval=5)

if env['SYSTEM'] == 'windows':
    env.Append( CXXFLAGS='/EHsc /MD /D _UNICODE /D WIN32 /D WINVER=0x0400 /D __WXMSW__ /D _WINDOWS', LINKFLAGS='/SUBSYSTEM:CONSOLE', TARGET_ARCH='x64' )
    MakeNewPathFile(libs_dirs[env['SYSTEM']].values())
    print '[!!!]     WAZNE: W przypadku szczesliwej kompilacji uruchom after_install.bat'




elif env['SYSTEM'] == 'linux':
    env.Append(CXXFLAGS="-DBOOST_LOG_DYN_LINK -w -std=c++11 -fno-permissive")

    #Aby aplikacja widziala biblioteki wspodzielone w folderze aplikacji
    env.Append( LINKFLAGS = Split('-z origin'), RPATH = env.Literal(os.path.join('\\$$ORIGIN')) )
    #Warunkowa kompilacja z liczeniem pokrycia.

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

if not conf.CheckCXXHeader('boost/python.hpp'):
    print 'Boost.Python not found!'
    Exit(1)

if not conf.CheckCXXHeader('boost/program_options.hpp'):
    print 'Boost::program_options not found!'
    Exit(1)

if not conf.CheckCXXHeader('boost/log/trivial.hpp'):
    print 'Boost::logging::trivial not found!'
    Exit(1)

env = conf.Finish()


if ARGUMENTS.get('coverage', 0) and env['SYSTEM']=='linux':
    print 'Coverage flag enabled'
    env.Append(CXXFLAGS="-fprofile-arcs -ftest-coverage", LINKFLAGS='-ftest-coverage')
    env['EXTERNAL_LIBS'].append('gcov')

if ARGUMENTS.get('debug', 0):
	print 'Debug flag enabled'
	if env['SYSTEM'] == 'windows':
		env.Append(CXXFLAGS='/D _DEBUG')
	elif env['SYSTEM'] == 'linux':
		env.Append(CXXFLAGS='-g')

if ARGUMENTS.get('optimize', 0):
	print 'Debug flag enabled'
	if env['SYSTEM'] == 'windows':
		env.Append(CXXFLAGS='/Ox')
	elif env['SYSTEM'] == 'linux':
		env.Append(CXXFLAGS='-O3')


#
# Kompilacja.
#
app = env.SConscript('src/SConscript',
           variant_dir = 'build/libs',
           duplicate = 0,
           exports = 'env libs')

# matlabScripts = env.SConscript('matlabScripts/SConscript',
#           variant_dir = 'build/scripts',
#           duplicate = 0,
#          exports = 'env')

#Testy
test = env.SConscript('test/SConscript',
           variant_dir = 'build/test',
           duplicate = 0,
           exports = 'env libs')


#Przyklady
examples = env.SConscript('examples/SConscript',
           variant_dir = 'build/examples',
           duplicate = 0,
           exports = 'env')


#Ciezko
docs = env.Docs("Foo", "Doxyfile")

#env.Depends(app, matlabScripts)
#all
Alias('all', app)
Alias('all', test)
Alias('all', examples)
Alias('all', docs)
#Alias('all', matlabScripts)

Help("""
    Available targets:
        scons           - default, build application+docs.
        scons docs      - build doxygen(equal to running doxygen).
        scons test      - builds all tests available in test/ directory.
        scons examples  - builds all files available in examples/ directory.
        scons all       - alias to build all targets mentioned above.

	Available flags:
		coverage=1		- enables gcov-related flags(linux only).
		debug=1			- enables debug flags.
""")
