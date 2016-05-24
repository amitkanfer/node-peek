{
    'targets': [
        {
            'target_name': 'peek',
            'sources': [ 'src/peek.cpp' ],
            'include_dirs': [
                '<!(node -e "require(\'nan\')")'
            ]
        }
    ]
}
