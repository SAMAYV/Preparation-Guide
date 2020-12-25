struct Job {
    ll a, b, idx;
    bool operator<(Job o) const {
        return min(a, b) < min(o.a, o.b);
    }
};

// or use sorting method min(a(j),b(j+1)) ≤ min(b(j),a(j+1))
vector<Job> johnsons_rule(vector<Job> jobs){
    sort(jobs.begin(),jobs.end());
    vector<Job> a, b;
    for(Job j : jobs){
        if(j.a < j.b){
            a.push_back(j);
        }
        else {
            b.push_back(j);
        }
    }
    a.insert(a.end(),b.rbegin(),b.rend());
    return a;
}

pair<ll,ll> finish_times(vector<Job> const& jobs){
    ll t1 = 0, t2 = 0;
    for(Job j : jobs){
        t1 += j.a;
        t2 = max(t2, t1) + j.b;
    }
    return make_pair(t1, t2);
}