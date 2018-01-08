# clipboard

get data(file path,text) from clipboard by nodejs. support win32 and osx

## build for nwjs

```shell
 nw-gyp rebuild --target=0.14.7 --arch=ia32
```

## build for nodejs

```shell
  node-gyp rebuild
```

## example

```js
const clipboard = require('clipboard');
let fileNames = clipboard.getFileNames();
let text = clipboard.getText();
```
