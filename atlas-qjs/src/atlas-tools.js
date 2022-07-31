/*
 * Get current timestamp
 */ 
function get_time() {
    var date = new Date()
    return date.getTime();
}

/*
 * get time diff in seconds
 */
function get_time_diff(end, start) {
    return ((end - start)/1000);
}

/*
 * get random integer
 */
function get_random_int(min, max) {
	min = Math.ceil(min);
	max = Math.floor(max);
	return Math.floor(Math.random() * (max - min) + min);
}

/*
 * generate a buffer of count size bytes given an input
 */
function repeat(pattern, count) {
    if (count < 1) return '';
    var result = '';
    while (count > 1) {
        if (count & 1) result += pattern;
        count >>= 1, pattern += pattern;
    }
    return result + pattern;
}

/*
 * Parse the command line arguments
 */
function parse_args(cmd) {
    // ignore the binary name
    let args = cmd.slice(1)
    let res = {}
    try {
        for (let i = 0; i < args.length; i++) {
            if(args[i].startsWith('--')) {
                if (parseInt(i) + 1 < args.length && !args[i+1].startsWith('--')) {
                    // strip the -- from the argument
                    args[i] = args[i].substring(2)
                    // parse the value
                    res[args[i]] = args[i+1]
                    i++
                } else {
                    // assign arg name as value
                    args[i] = args[i].substring(2)
                    res[args[i]] = true
                }
            }
        }
    } catch (e) {
        atlas_print("Error", e)
        usage();
    }
    return res
}

function tidy_file() {
    let time_diff = get_time_diff(get_time(), atlas.gstart_time);
    atlas_print("# Execution done: " + time_diff);
    //atlas_print(time_diff);
    if (atlas.log_name !== undefined) {
        atlas.log_file.close();
        std.popen('column -t ' + atlas.log_name + ' > .sorted_atlas; mv .sorted_atlas ' + atlas.log_name, "w");
    }
    // force connection stop
    atlas.atlas_scale('terminate', []);
    //atlas.start_wrapping(0);
    std.exit(0);
}

function atlas_print(...str) {
    if (atlas.log_name !== undefined) {
        var args = Array.prototype.slice.call(arguments);
        args.forEach(function(element) {
            atlas.log_file.printf("%s", element);
        }, this);
        atlas.log_file.printf("\n");
        atlas.log_file.flush();
    }
}

function usage() {
    print("Usage: quickjs daemon.js --log --servers x --file input.js\n" +
        "flags:\n" +
        "servers     \t Number of atlas node to use\n" + 
        "file        \t The source code to execute\n" +
        "server_file \t The file that contains the atlas nodes with ips\n" + 
        "log         \t Write atlas execution logs to file\n" + 
        "help        \t Show this usage message");
    std.exit(1)
}

function evaluate_args(opts) {
    if (opts["file"] !== undefined) {
	    atlas.file_to_exec = opts["file"]
    } else {
        print("Failed to provide the executable file, exiting")
        usage();
    }
    if (opts.hasOwnProperty("local")) {
        atlas.local_execution = true
    } else {
        if (opts["servers"] === undefined) {
            print("Set number of servers")
            usage()
        }
        set_worker_count(parseInt(opts["servers"]))
        set_server_count(parseInt(opts["servers"]))
        if (opts.hasOwnProperty("scaling")) {
            atlas.scaling = true
        } else {
            // since we are not using scaling, use all the workers without the local
            atlas.actual_workers = get_worker_count()
        }
        if (opts["server_file"] !== undefined)
            atlas.server_file = opts["server_file"]
        else
            atlas.server_file = "./atlas-addresses.txt"
    }
    if (opts["log"] !== undefined) {
        atlas.log_name = opts["log"];
        atlas.log_file = std.open(atlas.log_name, 'w');
    }
}

let number_of_servers = 0;
let number_of_workers = 0;
/*
 * the actual workers that currently can be used for scheduling
 */
atlas.actual_workers = 1
/******************************/
/*     Setters and Getters    */
/******************************/
function get_server_count() {
    return number_of_servers;
}
function get_worker_count() {
    return number_of_workers;
}
function set_server_count(n) {
    number_of_servers = n
}
function set_worker_count(n) {
    number_of_workers = n
}

atlas.file_to_exec = undefined;
atlas.scaling = false;
atlas.local_execution = false;
atlas.interval = -1;
atlas.wrapping_libs = false;
atlas.log_name = undefined;
let atlas_tools = {};
atlas_tools.get_server_count = get_server_count;
atlas_tools.get_worker_count = get_worker_count;
atlas_tools.set_server_count = set_server_count;
atlas_tools.evaluate_args = evaluate_args;
atlas_tools.get_time = get_time;
atlas_tools.get_time_diff = get_time_diff;
atlas_tools.get_random_int = get_random_int;
atlas_tools.repeat = repeat;
atlas_tools.parse_args = parse_args;
atlas_tools.tidy_file = tidy_file;
atlas_tools.usage = usage;
atlas_tools.atlas_print = atlas_print;
atlas.atlas_tools = atlas_tools;
