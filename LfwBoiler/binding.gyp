{
    'targets': [{
        'target_name': 'labfw_boiler',
        'sources': ['src/lab_boiler.cc'],
        "include_dirs": ["<!(node -e \"require('nan')\")"]
        }
    ]
}
