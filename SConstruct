import platform, os, glob

#Lokalizacja biblioteki Boost, dotyczy tylko Windowsow:
boost_prefix = "C:\\Program Files (x86)\\boost_1_59_0"

libs = ["Generator"]
libs_sources = map(lambda x: glob.glob('src/' + x + '/*.cpp'), libs) #[ glob.glob('src/Generator/*.cpp') , glob.glob('src/ObserverGUI/*.cpp') ]

program_sources = ['src/Main.cpp']
test_sources = Glob('test/*.cpp')

include_search_path = ['include'] + map(lambda x: 'src/' + x, libs)

env = Environment(CPPPATH=include_search_path,LIBPATH=['.'])
env['SYSTEM'] = platform.system().lower()


if env['SYSTEM'] == 'windows':
    env.Append( CCFLAGS=["/EHsc"] )
    env.Append(CPPPATH=boost_prefix)
    env.Append(LIBPATH=os.path.join(boost_prefix, 'stage\lib'))

elif env['SYSTEM'] == 'linux':
    env.Append(CXXFLAGS="-std=c++0x")
    env.Append(CPPPATH='/usr/include/')


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
for i in range(len(libs)):
    env.Library(libs[i], libs_sources[i])

testEnv = env.Clone()
#testEnv.Append(LIBPATH="src/")


#
# Targety
#
app = env.Program("app", program_sources, LIBS=libs)
Default(app)

apptest = ''

for i in range(len(libs)):
    apptest += testEnv.Program("test-" +libs[i]  , 'test/test_'+libs[i]+'.cpp', LIBS=libs)

Alias('test', apptest)

Alias('all', app)
Alias('all', apptest)
