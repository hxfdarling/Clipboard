# clipboard

get file path from win32 clipboard by nodejs

## build for nwjs

```shell
 nw-gyp rebuild --target=0.14.7 --arch=ia32
```

## example

```js
const clipboard = require('@moa/clipboard');let fileNames = clipboard.getFileNames();
```