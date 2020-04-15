project(
	'delaunay-triangulation',
	'cpp',
	version: '2.1.0',
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
	'-Wconversion',
	'-Wsign-conversion',
	'-Wno-format-nonliteral',
	'-Wfatal-errors',
	language: 'cpp',
)

if (get_option('buildtype') == 'release')
	# todo
endif

include = include_directories('include')

install_headers(
	'include/vector2.h',
	'include/edge.h',
	'include/triangle.h',
	'include/delaunay.h',
	subdir: 'dt',
)

lib_dt = shared_library(
	meson.project_name(),
	files(
		'dt/vector2.cpp',
		'dt/edge.cpp',
		'dt/triangle.cpp',
		'dt/delaunay.cpp',
	),
	version: meson.project_version(),
	include_directories: include,
	install: true,
)

dt = declare_dependency(
	link_with: lib_dt,
	include_directories: include,
)

catch2 = dependency('catch2', required : false)
if catch2.found()
	tests = executable(
		'tests',
		'tests/tests.cpp',
		dependencies: [dt, catch2],
	)
endif

sfml = dependency('sfml-graphics', required : false)
if sfml.found()
	example = executable(
		'example',
		'example/main.cpp',
		dependencies: [dt, sfml],
	)
endif
