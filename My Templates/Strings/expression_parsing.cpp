bool delim(char c){
    return c == ' ';
}
bool is_op(char c){
    return c == '+' || c == '-' || c == '*' || c == '/';
}
ll priority(char op){
    if(op == '+' || op == '-')
        return 1;
    if(op == '*' || op == '/')
        return 2;
    return -1;
}
void process_op(stack<ll>& st,char op){
    ll r = st.top(); st.pop();
    ll l = st.top(); st.pop();
    switch(op){
        case '+': st.push(l + r); break;
        case '-': st.push(l - r); break;
        case '*': st.push(l * r); break;
        case '/': st.push(l / r); break;
    }
}

// we assume that all operators are binary (i.e. they take two arguments), and all are left-associative 
// (if the priorities are equal, they get executed from left to right). Parentheses are allowed.

// Thus we learned how to calculate the value of an expression in O(n), at the same time we implicitly used the reverse Polish notation. 
// By slightly modifying the above implementation it is also possible to obtain the expression in reverse Polish notation in an explicit form.

ll evaluate(string& s){
    stack<ll> st;
    stack<char> op;
    REP(i,0,s.size()){
        if(delim(s[i])){
            continue;
        }
        if(s[i] == '('){
            op.push('(');
        } 
        else if(s[i] == ')'){
            while(op.top() != '('){
                process_op(st,op.top());
                op.pop();
            }
            op.pop();
        } 
        else if(is_op(s[i])){
            char cur_op = s[i];
            while(op.size() && priority(op.top()) >= priority(cur_op)){
                process_op(st, op.top());
                op.pop();
            }
            op.push(cur_op);
        } 
        else {
            ll number = 0;
            while(i < s.size() && isalnum(s[i])){
                number = number * 10 + s[i++] - '0';
            }
            --i;
            st.push(number);
        }
    }
    while(op.size()){
        process_op(st, op.top());
        op.pop();
    }
    return st.top();
}
