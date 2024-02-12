#!/usr/bin/env python3
# coding=utf-8

import os
import sys
from jinja2 import Environment, FileSystemLoader

def generate_thread_file(nb_args):
    # Create the jinja2 environment.
    # Notice the use of trim_blocks, which greatly helps control whitespace.
    j2_env = Environment(loader=FileSystemLoader(os.path.dirname(os.path.abspath(__file__))),
                         trim_blocks=True)
    with open(os.path.dirname(os.path.realpath(__file__)) + '/../../include/blet/thread.h', 'w+') as f:
        f.write(j2_env.get_template('thread.h.jinja').render(nb_args=nb_args))

if __name__ == '__main__':
    generate_thread_file(int(sys.argv[1]))
