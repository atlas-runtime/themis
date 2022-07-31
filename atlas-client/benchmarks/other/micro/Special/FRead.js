import * as std from 'std'

export function FRead_bench(read_size){

  let total_size = 4 * 1024 * 1000
  let buf_size = 20000000;
	let local_buffer = new ArrayBuffer(buf_size);
	
  let offset = 0;
  let file = std.open('./micro/Special/data','r');

  	while(true){
      let bytes = file.read( local_buffer, offset%total_size, read_size%buf_size);
      if(bytes == 0)break;
      offset+=read_size
  	}

    local_buffer = new ArrayBuffer(buf_size);
    offset = 0;
    file.close();
  
}
