//
// Created by mariocaster on 2/27/16.
//

#include "DesignPatterns.h"
#include "creational/builder/Cook.h"
#include "creational/builder/HawaiianPizzaBuilder.h"
#include "creational/builder/SpicyPizzaBuilder.h"
#include "creational/factory/ComputerFactory.h"
#include "creational/prototype/RecordFactory.h"
#include "creational/singleton/StringSingleton.h"
#include "structural/adapter/HinduFemale.cpp"
#include "structural/adapter/MuslimFemale.cpp"
#include "structural/adapter/MuslimRitual.cpp"
#include "structural/adapter/MuslimAdapter.cpp"
#include "structural/bridge/CircleShape.cpp"
#include "structural/bridge/DrawingAPI1.cpp"
#include "structural/bridge/DrawingAPI2.cpp"
#include "structural/composite/Ellipse.h"
#include "structural/composite/CompositeGraphic.h"
#include "structural/decorator/ClassDecoratorExample.h"

Singleton::StringSingleton *singleton = 0;

class CircleShape;

class DrawingAPI1;

void singletonTest(){
    std::cout << "Current var is " << Singleton::StringSingleton::instance()->GetString()
    << ", changing var to Sommerset" << std::endl;

    std::string newVal = "Sommerset";
    Singleton::StringSingleton::instance()->SetString(newVal);
}

void DesignPatterns::execute(int pattern) {
    switch (pattern) {
        case DESIGN_PATTERN_BUILDER: {
            PizzaBuilder::Cook cook;
            PizzaBuilder::HawaiianPizzaBuilder hpb;
            PizzaBuilder::SpicyPizzaBuilder spb;

            cook.makePizza(&hpb);
            cook.openPizza();

            cook.makePizza(&spb);
            cook.openPizza();
            break;
        }
        case DESIGN_PATTERN_FACTORY:{
            ComputerFactory::Computer* d = ComputerFactory::ComputerFactory::NewComputer("desktop");
            std::cout << "First computer is " << d->getName() << std::endl;

            ComputerFactory::Computer* l = ComputerFactory::ComputerFactory::NewComputer("laptop");
            std::cout << "Second computer is " << l->getName() << std::endl;
            break;
        }
        case DESIGN_PATTERN_PROTOTYPE:{
            PrototypeRecord::RecordFactory rf;
            auto r = rf.createRecord(PrototypeRecord::CAR);
            r->print();

            r = rf.createRecord(PrototypeRecord::BIKE);
            r->print();

            break;
        }
        case DESIGN_PATTERN_SINGLETON:{
            if (!singleton){
                singleton = new Singleton::StringSingleton;
            }

            std::string val = "Mills";
            Singleton::StringSingleton::instance()->SetString(val);

            singletonTest();
            val = Singleton::StringSingleton::instance()->GetString();

            std::cout << "Now the var is " << val << std::endl;

            break;
        }
        case DESIGN_PATTERN_ADAPTER:{
            HinduFemale* hinduGirl = new HinduFemale;
            MuslimFemale* muslimGirl = new MuslimFemale;
            MuslimRitual muslimRitual;
            MuslimAdapter* adaptedHindu = new MuslimAdapter(hinduGirl);
            muslimRitual.carryOutRitual(muslimGirl);
            muslimRitual.carryOutRitual(adaptedHindu);

            delete adaptedHindu;
            delete hinduGirl;
            delete muslimGirl;

            break;
        }
        case DESIGN_PATTERN_BRIDGE:{
            CircleShape circle1(1,2,3,new DrawingAPI1());
            CircleShape circle2(5,7,11,new DrawingAPI2());
            circle1.resizeByPercentage(2.5);
            circle2.resizeByPercentage(2.5);
            circle1.draw();
            circle2.draw();

            break;
        }
        case DESIGN_PATTERN_COMPOSITE: {
            //Initialize four ellipses
            const std::unique_ptr<Ellipse> ellipse1(new Ellipse());
            const std::unique_ptr<Ellipse> ellipse2(new Ellipse());
            const std::unique_ptr<Ellipse> ellipse3(new Ellipse());
            const std::unique_ptr<Ellipse> ellipse4(new Ellipse());

            //Initialize three composite graphics
            std::unique_ptr<CompositeGraphic> graphic(new CompositeGraphic());
            std::unique_ptr<CompositeGraphic> graphic1(new CompositeGraphic());
            std::unique_ptr<CompositeGraphic> graphic2(new CompositeGraphic());

            //Compose the graphics
            graphic1->add(ellipse1.get());
            graphic1->add(ellipse2.get());
            graphic1->add(ellipse3.get());

            graphic2->add(ellipse4.get());

            graphic->add(graphic1.get());
            graphic->add(graphic2.get());

            // Prints the complete graphic (four times the string "Ellipse")
            graphic->print();

            break;
        }
        case DESIGN_PATTERN_DECORATOR:
            ClassDecoratorExample b;
            b.execute();
            break;
        default: std::cout << "Pattern not recognized" << std::endl;
    }
}

std::string DesignPatterns::getDesignPatternName(int pattern) {
    switch (pattern) {
        case DESIGN_PATTERN_BUILDER: return "BUILDER";
        case DESIGN_PATTERN_FACTORY: return "FACTORY";
        case DESIGN_PATTERN_PROTOTYPE: return "PROTOTYPE";
        case DESIGN_PATTERN_SINGLETON: return "SINGLETON";
        case DESIGN_PATTERN_ADAPTER: return "ADAPTER";
        case DESIGN_PATTERN_BRIDGE: return "BRIDGE";
        case DESIGN_PATTERN_COMPOSITE: return "COMPOSITE";
        case DESIGN_PATTERN_DECORATOR: return "DECORATOR";
        default: return "design title not found";
    }
}

