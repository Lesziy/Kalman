import platform


common_sources = ['src/Foo.cpp']
program_sources = ['src/Main.cpp']
test_sources = ['src/test_foo.cpp']

include_search_path = ['include']

env = Environment(CPPPATH=[include_search_path],
                    CPPDEFINES=[],
                    LIBPATH=['.'],
                    LIBS=['boost_tests'],
                    CXXFLAGS="")

env['SYSTEM'] = platform.system().lower()

if env['SYSTEM'] == 'windows':
    env.Append( CCFLAGS=["/EHsc"] )

elif ENV['SYSTEM'] == 'linux':
    env.Append(CXXFLAGS="-std=c++0x")


env.Library("common", common_sources)
#testEnv = env.Clone()


env.Program("app", program_sources, LIBS=["common"])
#Repository('include')
