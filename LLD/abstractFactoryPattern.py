"""
Same as Factor pattern, only difference is that in abstract factory we have multiple layers of factories
and one factory will return objects of the lower level factory:

Vehicle (Factory)
    - Luxury Vehicle (Factory)
        - BMW (Low level object)
        - Audi (Low level object)
    - Ordinary Vehicle (Factory)
        - Tata (Low level object)
        - Honda (Low level object)

"""
