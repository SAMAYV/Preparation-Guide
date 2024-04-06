bool delim(char c){
    return c == ' ';
}
bool is_op(char c){
    return c == '+' || c == '-' || c == '*' || c == '/';
}
bool is_unary(char c){
    return c == '+' || c == '-';
}
ll priority(char op){
    if(op < 0) // unary operator
        return 3;
    if(op == '+' || op == '-')
        return 1;
    if(op == '*' || op == '/')
        return 2;
    return -1;
}
void process_op(stack<ll>& st,char op){
    if(op < 0){
        ll l = st.top(); st.pop();
        switch(-op){
            case '+': st.push(l); break;
            case '-': st.push(-l); break;
        }
    } 
    else {
        ll r = st.top(); st.pop();
        ll l = st.top(); st.pop();
        switch(op){
            case '+': st.push(l + r); break;
            case '-': st.push(l - r); break;
            case '*': st.push(l * r); break;
            case '/': st.push(l / r); break;
        }
    }
}

// Here is an implementation for the binary operators + − ∗ / and the unary operators + and −.
// In addition it should be noted, that some unary operators (e.g. unary plus and unary minus) are actually right-associative.

ll evaluate(string& s){
    stack<ll> st;
    stack<char> op;
    bool may_be_unary = true;
    REP(i,0,s.size()){
        if(delim(s[i])){
            continue;
        }
        if(s[i] == '('){
            op.push('(');
            may_be_unary = true;
        } 
        else if(s[i] == ')'){
            while(op.top() != '('){
                process_op(st, op.top());
                op.pop();
            }
            op.pop();
            may_be_unary = false;
        } 
        else if(is_op(s[i])){
            char cur_op = s[i];
            if(may_be_unary && is_unary(cur_op)){
                // done to distinguish b/w unary and binary operators
                cur_op = -cur_op;
            }
            while(!op.empty() && ((cur_op >= 0 && priority(op.top()) >= priority(cur_op)) || (cur_op < 0 && priority(op.top()) > priority(cur_op)))){
                process_op(st, op.top());
                op.pop();
            }
            op.push(cur_op);
            may_be_unary = true;
        } 
        else {
            ll number = 0;
            while(i < s.size() && isalnum(s[i])){
                number = number * 10 + s[i++] - '0';
            }
            --i;
            st.push(number);
            may_be_unary = false;
        }
    }
    while(!op.empty()){
        process_op(st, op.top());
        op.pop();
    }
    return st.top();
}