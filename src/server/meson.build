incdir = include_directories('../../include')
dep = []
src = []
src += files('./main.c', './sender.c', 'recver.c')

executable(
  'server',
  sources: src,
  dependencies : dep,
  include_directories : incdir,
  install : true)
