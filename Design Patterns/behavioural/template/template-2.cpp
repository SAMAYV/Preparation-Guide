class PastaDish {
    public:
    final void makeRecipe() {
        boilWater();
        addPasta();
        cookPasta();
        drainAndPlate();
        addSauce();
        addProtein();
        addGarnish();
    }
    protected:
    virtual void addSauce() = 0;
    virtual void addPasta() = 0;
    virtual void addProtein() = 0;
    virtual void addGarnish() = 0;
    private:
    void boilWater() {
        cout << "Boiling water" << endl;
    }
    void cookPasta() {
        cout << "Cooking pasta" << endl;
    }
    void drainAndPlate() {
        cout << "Draining and plating pasta" << endl;
    }
};

class SpaghettiMeatBalls : public PastaDish {
    protected:
    void addSauce() {
        cout << "Adding spaghetti sauce" << endl;
    }
    void addPasta() {
        cout << "Adding spaghetti" << endl;
    }
    void addProtein() {
        cout << "Adding meatballs" << endl;
    }
    void addGarnish() {
        cout << "Adding Parmesan cheese" << endl;
    }
};

class FettuccineAlfredo : public PastaDish {
    protected:
    void addSauce() {
        cout << "Adding Alfredo sauce" << endl;
    }
    void addPasta() {
        cout << "Adding fettuccine" << endl;
    }
    void addProtein() {
        cout << "Adding chicken" << endl;
    }
    void addGarnish() {
        cout << "Adding parsley" << endl;
    }
};
