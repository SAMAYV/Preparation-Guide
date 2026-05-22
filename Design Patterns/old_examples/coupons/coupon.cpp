class CouponDecorator : public Product {
    Product* product;
    double discountPercentage;
    public:
    CouponDecorator(Product* product, double discountPercentage) {
        this->product = product;
        this->discountPercentage = discountPercentage;
    }
    string getName() {
        return this->product->getName();
    }
    virtual double getPrice() = 0;
    virtual string getName() = 0;
};

class ProductTypeDiscountFactory {
    public:
    static double getProductTypeDiscount(Product* product) {
        if (product->getType() == ProductType::ELECTRONICS) {
            return 10;
        } else if (product->getType() == ProductType::CLOTHING) {
            return 20;
        } else if (product->getType() == ProductType::BOOKS) {
            return 30;
        } else if (product->getType() == ProductType::STATIONERY) {
            return 40;
        }
        return 0;
    }
};

class TypeCouponDecorator : public CouponDecorator {
    public:
    TypeCouponDecorator(Product* product) {
        // calculate discount percentage based on type
        CouponDecorator(product, ProductTypeDiscountFactory::getProductTypeDiscount(product));
    }
    double getPrice() {
        double originalPrice = this->product->getPrice();
        double discountAmount = originalPrice * this->discountPercentage / 100;
        cout << "Price of " << this->product->getName() << " after type coupon is: " << originalPrice - discountAmount << endl;
        return originalPrice - discountAmount;
    }
    string getName() {
        return this->product->getName() + " | type coupon";
    }
};

class PercentageCouponDecorator : public CouponDecorator {
    public:
    PercentageCouponDecorator(Product* product, double discountPercentage) : CouponDecorator(product, discountPercentage) {}
    double getPrice() {
        double originalPrice = this->product->getPrice();
        double discountAmount = originalPrice * this->discountPercentage / 100;
        cout << "Price of " << this->product->getName() << " after percentage coupon is: " << originalPrice - discountAmount << endl;
        return originalPrice - discountAmount;
    }
    string getName() {
        return this->product->getName() + " | percentage coupon";
    }
};

enum CouponType {
    TYPE,
    PERCENTAGE
};

class CouponFactory {
    public:
    static CouponDecorator* getCoupon(Product* product, CouponType couponType, double discountPercentage) {
        if (couponType == CouponType::TYPE) {
            return new TypeCouponDecorator(product);
        } else if (couponType == CouponType::PERCENTAGE) {
            return new PercentageCouponDecorator(product, discountPercentage);
        }
        return NULL;
    }
};