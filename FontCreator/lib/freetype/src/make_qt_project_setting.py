# -*- coding: utf8 -*-

import os
import os.path

for root, dirs, filenames in os.walk(u'.'):
    for filename in filenames:
        if '.c' in filename:
            filename = os.path.join(root, filename)
            filename = filename.replace('\\', '/')
            filename = filename.replace('./', 'lib/freetype/src/')
            filename = filename + ' \\'
            print filename