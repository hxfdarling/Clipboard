{
	"targets": [{
		"target_name": "binding",
		"sources": [
			"src/main.cc"
		],
    "conditions": [
			['OS=="mac"',
				{
          "sources":[
            "src/clip_osx.h",
            "src/clip_osx.mm"
          ],
					'defines': [
						'__MACOSX_CORE__',
            '__MAC__'
					],
					'link_settings': {
						'libraries': [
              '-framework Cocoa',
							'-framework CoreFoundation',
						]
					},
					'xcode_settings': {
						'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
						'OTHER_CFLAGS': [
							'-ObjC++',
							'-std=c++11'
						]
					}
				}
			],
			['OS=="win"',
				{
          "sources":[
            "src/clip_win.h",
            "src/clip_win.cc"
          ],
          'defines': [
						'__WIN32__'
					]
        }
			],
			['OS=="linux"',
				{}
			]
		]
	}]
}