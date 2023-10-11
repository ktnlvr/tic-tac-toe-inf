incdir = include_directories('../../include')
dep = []
dep += dependency('curses')
src = []
src += files('./main.c', 'sender.c', 'recver.c', 'tui.c')
executable('client-tui', src, dependencies:dep, install:true, include_directories:incdir, link_with:lib)
