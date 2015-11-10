import platform, os

#Lokalizacja biblioteki Boost, dotyczy tylko Windowsow:
boost_prefix = "C:\\Program Files (x86)\\boost_1_59_0"

common_sources = ['src/Foo.cpp']
program_sources = ['src/Main.cpp']
test_sources = Glob('test/*.cpp')

include_search_path = ['include']

env = Environment(CPPPATH=[include_search_path],
                    CPPDEFINES=[],
                    LIBPATH=['.'],
                    LIBS=['boost_tests'],
                    CXXFLAGS="")

env['SYSTEM'] = platform.system().lower()

if env['SYSTEM'] == 'windows':
    env.Append( CCFLAGS=["/EHsc"] )
    env.Append(CPPPATH=boost_prefix)
    env.Append(LIBS=os.path.join(boost_prefix, 'stage\lib'))

elif env['SYSTEM'] == 'linux':
    env.Append(CXXFLAGS="-std=c++0x")
    env.Append()

#
# Czas konfiguracji.
#
conf = Configure(env)

if not conf.CheckCXXHeader('boost/log/trivial.hpp'):
    print 'Boost.Log not found!'
    Exit(1)

if not conf.CheckCXXHeader('boost/test/included/unit_test.hpp'):
    print 'Boost.Test not found!'
    Exit(1)

env = conf.Finish()

#
# Kompilacja.
#
env.Library("common", common_sources)
testEnv = env.Clone()
testEnv.Append(LIBPATH="src/")

app = env.Program("app", program_sources, LIBS=["common"])
Default(app)

apptest = testEnv.Program("app-test", test_sources, LIBS=["common"])
Alias('test', apptest)
