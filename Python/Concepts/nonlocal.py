def fun():
    var1 = 10
 
    def gun():
        # tell python explicitly that it 
        # has to access var1 initialized 
        # in fun on line 2
        # using the keyword nonlocal
        nonlocal var1
        var1 = var1 + 10
        print(var1)
 
    gun()
fun()

# In this example, before initializing var1 in gun(). We have explicitly told Python that, do not initialize a new variable, instead access var1 present already on line 2. 
# using the keyword nonlocal So when the interpreter performs addition, it access the value 10(already present) and error is avoided.