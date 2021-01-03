// https://www.spoj.com/problems/HORRIBLE/

struct node {
    ll value;
    ll lazy;
    node *l, *r;
    node(){
        value = lazy = 0;
        l = r = NULL;
    }
};

void lazy(node *&t,ll start,ll end){
    if(t->lazy != 0){
        t->value += t->lazy * (end - start + 1);
        // if t is not a leaf
        if(start < end){
            if(t->l == NULL) t->l = new node();
            if(t->r == NULL) t->r = new node();
            t->l->lazy += t->lazy;
            t->r->lazy += t->lazy;
        }
        t->lazy = 0;
    }
}

void update(node *&t,ll start,ll end,ll left,ll right,ll v){
    // if t == NULL then t hasn't been visited and hasn't been passed any lazy value
    if(t == NULL) t = new node();
    else lazy(t,start,end);

    if(start > right || end < left){
        return;    
    } 
    if(start >= left && end <= right){
        t->value += v*(end - start + 1);
        if(start < end){
            if(t->l == NULL) t->l = new node();
            if(t->r == NULL) t->r = new node();
            t->l->lazy += v;
            t->r->lazy += v;
        }
        return;
    }
    ll mid = (start + end) >> 1;
    update(t->l, start, mid, left, right, v);
    update(t->r, mid + 1, end, left, right, v);
    t->value = t->l->value + t->r->value;
}

ll query(node *t,ll start,ll end,ll left,ll right){
    if(t == NULL) return 0;
    lazy(t, start, end);
    if(start > right || end < left) return 0;
    if(start >= left && right >= end){
        return t->value;    
    } 
    ll mid = (start + end) >> 1;
    return get(t->l, start, mid, left, right) + get(t->r, mid + 1, end, left, right);
}

// free memory
void del(node *&t){
    if(t == NULL) return;
    del(t->l);
    del(t->r);
    delete t;
}

int main() 
{
    ll test;
    scanf("%lld", &test);
    while(test--){
        node *t = NULL;
        ll n, c;
        scanf("%lld %lld", &n, &c);
        while(c--){
            ll i;
            scanf("%lld", &i);
            if(i == 0){
                ll p, q, v;
                scanf("%lld %lld %lld", &p, &q, &v);
                update(t, 1, n, p, q, v);
            } 
            else {
                ll p, q;
                scanf("%lld %lld", &p, &q);
                printf("%lld\n", query(t, 1, n, p, q));
            }
        }
        del(t);
    }
}