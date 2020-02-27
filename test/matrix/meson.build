matrix_exe = executable('main.cpp.executable', 
    sources: ['main.cpp'],
    dependencies: matrix,
    install : true)

test_matrix_exe = executable('test_Matrix.cpp.executable', 
    sources: ['test_Matrix.cpp'], 
    dependencies : [matrix, gtest_dep])
test('my Matrix test', test_matrix_exe)
