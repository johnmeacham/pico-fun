include <BOSL2/std.scad>

$fn = 32;
screw_distances = [19, 18, 72];
dim = [57.2, 78.2];
odim = [dim.x + 3, dim.y + 3];
pcb_thick = 1.5;
solder_clearance = 4 - pcb_thick;

module holes() {
        ydistribute(screw_distances[2]) {
                xcopies(screw_distances[0])
                    children();
                xcopies(screw_distances[1])
                    children();
        }
}

down(2)
    linear_extrude(2)
    difference() {
        rect(odim, rounding = 2);
        holes()circle(d = 2.8);
}

linear_extrude(solder_clearance)
    difference() {
        holes()circle(d = 5);
        holes()circle(d = 2.8);
}

linear_extrude(solder_clearance + pcb_thick)
    difference() {
        rect(odim, rounding = 2);
        rect(dim);
}

linear_extrude(solder_clearance) {
        back(10) rect([10, 50]);
        difference() {
                rect(odim, rounding = 2);
                rect([dim.x - 8 * 2, dim.y]);
        }
}
