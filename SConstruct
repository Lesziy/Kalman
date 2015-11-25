import platform, os, glob

#Lokalizacja biblioteki Boost, dotyczy tylko Windowsow:
#
boost_include_prefix = "C:\\Boost\\include\\boost-1_59"
boost_lib_prefix = "C:\Boost\lib"
SDL_prefix = "C:\\Program Files (x86)\\SDL"

libs = ["Generator", "SimpleSDL"]

external_libs = ['SDL2', 'SDL2main']# ["python27"] humor: lib pythona to python27 pod windowsem, python2.7 pod linuxami...


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
env.VariantDir('bin', 'src')
#env['STATIC_AND_SHARED_OBJECTS_ARE_THE_SAME']=1
env['SYSTEM'] = platform.system().lower()


if env['SYSTEM'] == 'windows':
    env.Append( CXXFLAGS='/EHsc /MDd', LINKFLAGS='/SUBSYSTEM:CONSOLE /NODEFAULTLIB:msvcrt' )
    env.Append(CPPPATH=[SDL_prefix + '\include', boost_include_prefix, 'C:\Python27\include'])
    env.Append(LIBPATH=[boost_lib_prefix,'C:\Python27\libs', os.path.join(SDL_prefix, 'lib\\x64')])
    external_libs.append("python27")
    external_libs.append("legacy_stdio_definitions")
#    external_libs.append("SDL2.lib")

elif env['SYSTEM'] == 'linux':
    env.Append(CXXFLAGS="-std=c++0x")
    env.Append(CPPPATH='/usr/include/python2.7', LIBPATH='/usr/lib64/python2.7')
    external_libs.append(["python2.7", "boost_python"])
    env.Append( LINKFLAGS = Split('-z origin'), RPATH = env.Literal(os.path.join('\\$$ORIGIN')) ) #Aby aplikacja widziala biblioteki wspodzielone w folderze aplikacji

#
# Konfiguracja
#
conf = Configure(env)

print '[DEBUG]'
print external_libs

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

if not conf.CheckLib('SDL2main'):
        print 'SDL2 lib not found, exiting!'
        Exit(1)

if env['SYSTEM'] == 'linux':
    #Ten test nie dziala pod Windowsem.
    if not conf.CheckCHeader('boost/python.hpp'):
        print 'Boost.Python not found!'
        Exit(1)

env = conf.Finish()

#
# Kompilacja.
#

#Windows
for i in range(len(libs)):
    libs_shared += env.Library(libs[i], libs_sources[i], LIBS=external_libs)
testEnv = env.Clone()
#testEnv.Append(LIBPATH="src/")


#
# Targety
#

#Domyslny
app = env.Program("app", program_sources, LIBS=libs+external_libs)
env.Depends(app, libs_shared)

#Default(libs_shared)
Default(app)

#Testy
for i in range(len(libs)):
    apptest += testEnv.Program("test-" +libs[i]  , 'test/test_'+libs[i]+'.cpp', LIBS=external_libs+libs)

#Przyklady
for j in examples_sources:
    examples += testEnv.Program(os.path.splitext(os.path.split(j)[1])[0],j, LIBS=external_libs+libs)

Alias('test', apptest)
Alias('examples', examples)

#all
Alias('all', app)
Alias('all', apptest)
Alias('all', examples)
