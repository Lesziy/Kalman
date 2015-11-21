#!/bin/python
import sys, os, string;

project_dir = os.path.join(os.getcwd(), '..')

header_template = """#pragma once

class $name 
{
    
    public:
        ${name}();
        ~${name}();
};

"""

src_template = """#include "${name}.h"

${name}::${name}() 
{
}

${name}::~${name}()
{
}
"""

test_template = """
#define BOOST_TEST_MODULE ${name} test module
#include <boost/test/included/unit_test.hpp>
#include "${name}.h"

using namespace boost::unit_test;


BOOST_AUTO_TEST_SUITE(test_${name})
BOOST_AUTO_TEST_CASE(test_true)
{
	${name} Foo();
	BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()

"""
def new_folder(step, fld, name):
    what = os.path.join(fld, name)
    print("Step " + step + ": creating " + what)
    
    dirname = os.path.join(project_dir,what)
    if os.path.exists(dirname):
        print("Module exists!\nExiting...\n")
        return 1
    else:
        os.mkdir(dirname)


def new_file(step, name, where, what, src):
    path = os.path.join(project_dir, where, what)
    print("Step " + step + ": creating " + path)
    
    if os.path.exists(path):
        print("Module exists!\nExiting...\n")
        return 1
    else:
        with open(path, 'w') as f:
            f.write(src)

     

def new_module(name):
    new_folder('one', 'src', name)
    
    new_file('three', name, 'include', name+'.h', string.Template(header_template).substitute(name=name))
    new_file('four', name, os.path.join('src', name), name+'.cpp', string.Template(src_template).substitute(name=name))
    new_file('five', name, 'test', 'test_'+name+'.cpp', string.Template(test_template).substitute(name=name))
        
    
        
    
    
        

ret = new_module(sys.argv[1])
sys.exit(ret)


