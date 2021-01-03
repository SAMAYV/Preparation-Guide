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

// This function works in O(lognlogm) time, since it first descends the free in the first coordinate, and 
// for each traversed vertex in the tree it makes a query in the corresponding Segment Tree along the second coordinate.

ll query_y(ll treenodex,ll treenodey,ll starty,ll endy,ll lefty,ll righty){
    if(righty < starty || endy < lefty){
        return 0;
    }
    if(lefty <= starty && righty >= endy){
        return tree[treenodex][treenodey];
    }
    ll midy = (starty + endy) / 2;
    return query_y(treenodex,treenodey*2,starty,midy,lefty,righty) 
    	 + query_y(treenodex,1 + treenodey*2,midy+1,endy,lefty,righty);
}
ll query_x(ll treenodex,ll startx,ll endx,ll leftx,ll rightx,ll lefty,ll righty){
    if(rightx < startx || endx < leftx){
        return 0;
    }
    if(leftx <= startx && rightx >= endx){
        return query_y(treenodex, 1, 0, m-1, lefty, righty);
    }
    ll midx = (startx + endx)/2;
    return query_x(treenodex*2, startx, midx, leftx, rightx, lefty, righty)
         + query_x(treenodex*2 + 1, midx+1, endx, leftx, rightx, lefty, righty);
}

void update_y(ll treenodex,ll startx,ll endx,ll treenodey,ll starty,ll endy,ll x,ll y,ll new_val){
    if(starty == endy){
        if(startx == endx){
            tree[treenodex][treenodey] = new_val;
        }
        else {
            tree[treenodex][treenodey] = tree[treenodex*2][treenodey] + tree[treenodex*2+1][treenodey];
        }
    } 
    else {
        ll midy = (starty + endy)/2;
        if(y <= midy){
            update_y(treenodex, startx, endx, treenodey*2, starty, midy, x, y, new_val);
        }
        else {
            update_y(treenodex, startx, endx, treenodey*2+1, midy+1, endy, x, y, new_val);
        }
        tree[treenodex][treenodey] = tree[treenodex][treenodey*2] + tree[treenodex][treenodey*2+1];
    }
}
void update_x(ll treenodex,ll startx,ll endx,ll x,ll y,ll new_val){
    if(startx != endx){
        ll midx = (startx + endx)/2;
        if(x <= midx){
            update_x(treenodex*2, startx, midx, x, y, new_val);
        }
        else {
            update_x(treenodex*2+1, midx+1, endx, x, y, new_val);
        }
    }
    update_y(treenodex, startx, endx, 1, 0, m-1, x, y, new_val);
}