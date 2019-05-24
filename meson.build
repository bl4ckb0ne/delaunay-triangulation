project(
	'delaunay-triangulation',
	'cpp',
	version: '2.0.0',
	license: 'MIT',
	meson_version: '>=0.50.0',
	default_options: [
		'cpp_std=c++17',
		'warning_level=3',
		'werror=true',
		'buildtype=debug',
	],
)

add_project_arguments(
	'-Wshadow',
	'-Wnon-virtual-dtor',
	'-Wold-style-cast',
	'-Wcast-align',
	'-Wunused',
	'-Woverloaded-virtual',
	'-Wpedantic',
	'-Wconversion',
	'-Wsign-conversion',
	'-Wno-format-nonliteral',
	language: 'cpp',
)

if (get_option('buildtype') == 'release')
	# todo
endif

include = include_directories('include')

install_headers(
	'include/delaunay.h',
	subdir: 'dt',
)

lib_dt = shared_library(
	meson.project_name(),
	files(
		'dt/numeric.cpp',
	),
	version: meson.project_version(),
	include_directories: include,
	install: true,
)

dt = declare_dependency(
	link_with: lib_dt,
	include_directories: include,
)

catch2 = dependency('catch2')
tests = executable(
	'tests',
	'tests/tests.cpp',
	dependencies: [dt, catch2],
)

sfml = dependency('sfml-graphics')
example = executable(
	'example',
	'example/main.cpp',
	dependencies: [dt, sfml],
)
