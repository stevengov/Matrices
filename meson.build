project( 'matrix', 'cpp',
    version : '0.0.1',
    default_options : ['warning_level=3',
                       'b_coverage=true',
                       'cpp_std=c++14'])

subdir('src')

# === test dependencies ===
gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_main_dep')
if not gtest_dep.found()
  error('MESON_SKIP_TEST: gtest not installed.')
endif
# === end test dependencies ===
subdir('test')
