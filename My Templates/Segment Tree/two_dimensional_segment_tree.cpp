// A matrix a[0…n−1,0…m−1] is given, and we have to find the sum (or minimum/maximum) on some submatrix a[x1…x2,y1…y2], as well as 
// perform modifications of individual matrix elements (i.e. queries of the form a[x][y]=p).
// So we build a 2D Segment Tree: first the Segment Tree using the first coordinate (x), then the second (y).

// Such a Segment Tree still uses a linear amount of memory, but with a larger constant: 16nm
void build_y(ll treenodex,ll startx,ll endx,ll treenodey,ll starty,ll endy){
    if(starty == endy){
        if(startx == endx){
            tree[treenodex][treenodey] = arr[startx][starty];
        }
        else {
            tree[treenodex][treenodey] = tree[treenodex*2][treenodey] + tree[treenodex*2+1][treenodey];
        }
    } 
    else {
        ll midy = (starty + endy) / 2;
        build_y(treenodex, startx, endx, treenodey*2, starty, midy);
        build_y(treenodex, startx, endx, treenodey*2+1, midy+1, endy);
        tree[treenodex][treenodey] = tree[treenodex][treenodey*2] + t[treenodex][treenodey*2+1];
    }
}
void build_x(ll treenodex,ll startx,ll endx){
    if(startx != endx){
        ll midx = (startx + endx) / 2;
        build_x(treenodex*2, startx, midx);
        build_x(treenodex*2+1, midx+1, endx);
    }
    build_y(treenodex, startx, endx, 1, 0, m-1);
}


ll sum_y(int vx, int vy, int tly, int try_, int ly, int ry) {
    if (ly > ry) 
        return 0;
    if (ly == tly && try_ == ry)
        return t[vx][vy];
    int tmy = (tly + try_) / 2;
    return sum_y(vx, vy*2, tly, tmy, ly, min(ry, tmy))
         + sum_y(vx, vy*2+1, tmy+1, try_, max(ly, tmy+1), ry);
}
ll sum_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
    if (lx > rx)
        return 0;
    if (lx == tlx && trx == rx)
        return sum_y(vx, 1, 0, m-1, ly, ry);
    int tmx = (tlx + trx) / 2;
    return sum_x(vx*2, tlx, tmx, lx, min(rx, tmx), ly, ry)
         + sum_x(vx*2+1, tmx+1, trx, max(lx, tmx+1), rx, ly, ry);
}

void update_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int new_val) {
    if (ly == ry) {
        if (lx == rx)
            t[vx][vy] = new_val;
        else
            t[vx][vy] = t[vx*2][vy] + t[vx*2+1][vy];
    } else {
        int my = (ly + ry) / 2;
        if (y <= my)
            update_y(vx, lx, rx, vy*2, ly, my, x, y, new_val);
        else
            update_y(vx, lx, rx, vy*2+1, my+1, ry, x, y, new_val);
        t[vx][vy] = t[vx][vy*2] + t[vx][vy*2+1];
    }
}
void update_x(int vx, int lx, int rx, int x, int y, int new_val) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        if (x <= mx)
            update_x(vx*2, lx, mx, x, y, new_val);
        else
            update_x(vx*2+1, mx+1, rx, x, y, new_val);
    }
    update_y(vx, lx, rx, 1, 0, m-1, x, y, new_val);
}