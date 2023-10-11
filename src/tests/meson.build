incdir = include_directories('../../include')
e = executable('board_tests', 'test_board.c', include_directories:incdir, link_with:lib)
test('Board', e, is_parallel:true)
