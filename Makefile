name: "swiftly_joinleave Compiler"

on:
  push:
    branches:
      - "*"
  pull_request:

jobs:
  build:
    name: Build
    runs-on: ${{ matrix.os }}

    container: ${{ matrix.container }}
    strategy:
      fail-fast: false
      matrix:
        os: [ubuntu-latest, windows-latest]
        include:
          - os: windows-latest
          - os: ubuntu-latest
            container: registry.gitlab.steamos.cloud/steamrt/sniper/sdk

    steps:
      - name: Checkout
        uses: actions/checkout@v4
        with:
          path: addons/swiftly/plugins/swiftly_joinleave
          submodules: recursive

      - name: Checkout Swiftly
        uses: actions/checkout@v4
        with:
          repository: swiftly-solution/swiftly
          ref: master
          path: addons/swiftly

      - name: Installing Swiftly Scripting files
        run: |
          cd addons/swiftly
          mv plugin_files/scripting/* ..
          cd ..

      - name: Build
        working-directory: addons/swiftly/plugins/swiftly_joinleave
        run: |
          make

      - name: Upload Files - Linux
        if: matrix.os == 'ubuntu-latest'
        uses: actions/upload-artifact@v3
        with:
          name: swiftly_joinleave Plugin - Linux
          path: ${{ github.workspace }}/addons/swiftly/plugins/swiftly_joinleave/output/swiftly_joinleave.so

      - name: Upload Files - Windows
        if: matrix.os == 'windows-latest'
        uses: actions/upload-artifact@v3
        with:
          name: swiftly_joinleave Plugin - Windows
          path: ${{ github.workspace }}/addons/swiftly/plugins/swiftly_joinleave/output/swiftly_joinleave.dll
