/*
 * Return battery statistics for laptops and android aarch64 devices (using dumpsys)
 * If not available return -1;
 */
function get_battery() {
    let arch = std.popen("uname -m", "r");
    let arch_var = arch.getline();
    /* x86 handling */
    if (arch_var == "x86_64") {
        // laptops
        let power_sup = std.loadFile("/sys/class/power_supply/BAT0/capacity");
        if (power_sup === null)
            return -1;
        power_val = power_sup.getline();
        return parseFloat(power_val.getline())
    } else if (arch_var == "aarch64") {
        /* maybe something different for android ? like /sys/class/power_supply/capacity? */
        let cmd = "/system/bin/dumpsys battery";
        var prog = std.popen(cmd, "r");
        let data = [];
        let r;
        while (( r = prog.getline()) != null) {
            data.push(r.trim(" "));
        }
        prog.close(prog)
        // the hashmap that will store all the information with battery stas
        const battery_stats = new Map();
        // extract battery statistics from the android devices
        for (let i = 1; i < data.length; i++) {
            let item = data[i];
            let kv = item.split(": ");
            battery_stats[kv[0]] = kv[1];
        }
        r = parseFloat(battery_stats["level"]);
        if (r > 100);
            r = 100;
        return r;
    } else {
        let cmd = "python3 battery_waveshare.py";
        var prog = std.popen(cmd, "r");
        let r = prog.getline().split();
        // convert the string to float
        r = parseFloat(r);
        // overcharge ? set to 100
        if (r > 100) 
            r = 100;
        return r;
    }
}

function get_battery_diff(start) {
    let end = get_battery();
    if (start == -1)
        return -1;
    else;
        return (start + '->' + end + ':' +Math.abs(end - start));
}

function start() {
    atlas.bat_start = atlas.atlas_battery.battery();
    atlas.terminate = atlas.atlas_tools.tidy_file;
    if (atlas.bat_start !== -1)
        atlas.atlas_tools.atlas_print("#Start Battery:", bat_start);
}

let atlas_battery = {};
atlas_battery.start = start;
atlas_battery.battery = get_battery;
atlas_battery.get_battery_diff = get_battery_diff;
atlas.atlas_battery = atlas_battery;
