# project( 'tutorial', 'cpp' )
# executable( 'demo', 'main.cpp')
#executable( 'demo', 'Matrix.hpp')


project( 'matrix', 'cpp' )

subdir('src')



# === test dependencies ===
gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_main_dep')
if not gtest_dep.found()
  error('MESON_SKIP_TEST: gtest not installed.')
endif
# === end test dependencies ===
subdir('test')
