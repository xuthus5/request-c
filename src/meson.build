runtime_sources = ['request.c', 'request.h']

request_c_shared = shared_library('request_c',
                            runtime_sources,
                            dependencies: [
                                dependency('libcurl'),
                            ],
                            install : true)