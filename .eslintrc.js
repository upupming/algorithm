module.exports = {
  root: true,
  extends: ['standard-with-typescript'],
  globals: { _: true },
  parserOptions: {
    project: './tsconfig.json'
  },
  rules: {
    '@typescript-eslint/naming-convention': [
      'error',
      {
        selector: 'interface',
        format: ['PascalCase'],
        custom: {
          regex: '^I[A-Z]',
          match: true
        }
      }
    ],
    '@typescript-eslint/explicit-function-return-type': 0,
    '@typescript-eslint/strict-boolean-expressions': 0,
    'no-console': 0,
    '@typescript-eslint/no-non-null-assertion': 0,
    '@typescript-eslint/brace-style': 0,
    'no-return-assign': 0
  },
  overrides: [
    {
      files: ['./*.js', './*.ts'],
      rules: {
        'import/no-anonymous-default-export': 0,
        'filenames/match-exported': 0
      }
    }
  ]
}
