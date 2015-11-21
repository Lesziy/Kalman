import platform, os, glob

#Lokalizacja biblioteki Boost, dotyczy tylko Windowsow:
#
boost_prefix = "C:\\Program Files (x86)\\boost_1_59_0"


libs = ["Generator"]

external_libs = []# ["python27"] humor: lib pythona to python27 pod windowsem, python2.7 pod linuxami...


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


if env['SYSTEM'] == 'windows':
    env.Append( CCFLAGS=["/EHsc"] )
    env.Append(CPPPATH=[boost_prefix, 'C:\Python27\include'])
    env.Append(LIBPATH=[os.path.join(boost_prefix, 'stage\lib'),'C:\Python27\libs'])
    external_libs.append("python27")

elif env['SYSTEM'] == 'linux':
    env.Append(CXXFLAGS="-std=c++0x")
    env.Append(CPPPATH='/usr/include/python2.7', LIBPATH='/usr/lib64/python2.7')
    external_libs.append(["python2.7", "boost_python"])
    env.Append( LINKFLAGS = Split('-z origin'), RPATH = env.Literal(os.path.join('\\$$ORIGIN')) ) #Aby aplikacja widziala biblioteki wspodzielone w folderze aplikacji
 

#
# Konfiguracja
#
conf = Configure(env)

if not conf.CheckCXXHeader('boost/test/included/unit_test.hpp'):
    print 'Boost.Test not found!'
    Exit(1)

env = conf.Finish()

#
# Kompilacja.
#

#Windows
if env['SYSTEM'] == 'windows':
    for i in range(len(libs)):
        libs_shared += env.StaticLibrary(libs[i], libs_sources[i])

if env['SYSTEM'] == 'linux':
    for i in range(len(libs)):
        libs_shared += env.SharedLibrary(libs[i], libs_sources[i])

testEnv = env.Clone()
#testEnv.Append(LIBPATH="src/")


#
# Targety
#

#Domyslny
app = env.Program("app", program_sources, LIBS=external_libs+libs)
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
