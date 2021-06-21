# annoy-node

Typescript typed Node bindings for [Annoy](https://github.com/spotify/annoy), an efficient Approximate Nearest Neighbors implementation written in C++.

Most of the [Python API](https://github.com/spotify/annoy#full-python-api) methods are implemented.

- `addItem`
- `build`
- `save`
- `load`
- `unload`
- `getItem`
- `getNNsByVector`
- `getNNsByItem`

## Installation

Supports Linux, Windows, and MacOS. Node version >= 14. Prebuilt binaries are already updated if not available for your configuration then you need to require [cmake](https://cmake.org/) in path then install cmake-js globally

    npm install -g cmake-js

Make sure you have valid C++ compiler

Then:

    npm install annoy
    or
    yarn add annoy-node

## Usage

```ts
import Annoy, { Metric } from "../dist";
const annoy = new Annoy(128, Metric.ANGULAR);

for (let i = 0; i < 1000; i += 1) {
  const vector = new Float64Array(128);
  for (let v = 0; v < 128; v += 1) {
    vector[v] = Math.random();
  }
  annoy.addItem(i, vector);
}
annoy.build(10);
const result = annoy.get_nns_by_item(0, 2, true);
console.log(result);
```

## Development

    npm install -g cmake-js
    cmake-js rebuild

## Contribution

PRs are welcome

## License

The MIT License (MIT)

Copyright (c) 2021 Prathamesh Netake

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
