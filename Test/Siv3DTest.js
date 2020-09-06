Module.preRun = [
  function () 
  {
    FS.mkdir('/test');
    FS.mount(NODEFS, { root: './test' }, '/test');
  }
]