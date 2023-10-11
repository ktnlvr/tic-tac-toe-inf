incdir = include_directories('../../include')
dep = []
src = []
src += files('./main.c', 'sender.c', 'recver.c')
executable('client-tui', src, dependencies:dep, install:true, include_directories:incdir, link_with:lib)
