Team Number: 010-25


Team Names: 
    Ben Pullis - pulli068, Divyesh Thirukonda - thiru063, Adam Douiri - douir002, Owen Liu - liu02753


Overview: 
    This project is a drone delivery simulation written primarily in C++. The user can interact with the simulation by adding a source and destination for the drone to deliver its package. To make the simulation more realistic and lively, we added entities such as a human, helicopter, and robots. There is also a notification panel with important information passed through it. With our latest additions, humans can get sick and spread their diseases with each other. HelperDrones can assist in deliveries whenever a LeaderDrone is low on battery. There is a wind system that applies wind to Drones in the air and does damage to the Drones until they are unusable. [TODO Owen: describe your additions in one sentence]


Instructions:
    Build: "make clean; make -j"
    Run: "make run"
    Multi-Drone:
        Add a few HelperDrones and schedule some deliveries, after some time the LeaderDrone 
        will run low on battery and need to recharge. At this point you will notice the 
        closest HelperDrone head to receive the package in a handoff and the LeaderDrone 
        will go and recharge at the charging station. 
    Severe Weather:
        You can see the effect in real time at the start of the simulation after spawning in a
        Drone of any type (LeaderDrone, or HelperDrone). The Drone will have a wind effect on it,
        and after a certain amount of time (based on the magnitude), the durability will hit 0. I
        would recommend setting the simulation to maximum speed in order to see this entire cycle,
        and see the effects of wind over long periods of time.
    [TODO Owen: describe your additions in one sentence]
    Plague:
        To see the effect in real time, add a bunch of humans to the simulation.
        Then click on 'Create Disease' and add your desired values.
        Finally, launch the disease and see what happens to it!


Requirements:

    Ben Pullis - Multi-Drone:
        The Multi-Drone System shall LeaderDrones and HelperDrones
        The Multi-Drone System shall have a singular recharge station for charging drones
        When a LeaderDrone encounters low battery (less than 20%), the Multi-Drone System shall request a handoff to a HelperDrone
        When a handoff occurs or is requested, the Multi-Drone System shall send a notification to the front end
        When a handoff is requested, the Multi-Drone System shall find the closest HelperDrone to complete the handoff
        If there are no HelperDrones, then the LeaderDrone shall recharge before completing its delivery
        While the HelperDrone is completing the delivery the LeaderDrone shall recharge at the recharge station
        While the LeaderDrone is completing the delivery the HelperDrones shall sit idle waiting for a request
    
    Divyesh Thirukonda - Plague:
        The system shall always monitor the proximity of all humans and update their observer status (distance from each other) in real time using the observer pattern
        While a humans is ill, it should gradually be less ill (duration of illness decreases as time goes on)
        When the human sneezes and at least one human is nearby, the human shall publish the disease all nearby humans (as humans are publishers)
        The human shall always listen for incoming diseases (as humans are also observers)
        When a human receives a disease, the human shall decide whether to accept, reject, or accept an altered version using the strategy pattern.
        When a human's sum of all disease's severities are greater than or equal to 10, the human shall die and be removed from the simulation.
        If the human moves out of the disease-spreading radius of another human’s disease, then the system shall unsubscribe the human from the publishing human

    Adam Douiri - Severe Weather:
        The SevereWeatherSystem shall have a single, continuously updating weather system (singleton), which generates wind by sampling random noise from a normal distribution every second.
        The DroneWindDecorator shall fetch the wind speed from the severe weather system every update tick.
        The DroneWindDecorator shall decrease drone durability and speed by a factor that is proportional to the magnitude of the wind and effective time every update tick.
        The DroneWindDecorator shall adjust the drone’s displacement by the windSpeed every update tick.
        When a Drone of any type is created, the Factory shall wrap a DroneWindDecorator around it.
        When the DroneWindDecorator has hit 0 durability, the drone shall notify the system that the drone has failed due to adverse weather conditions, and the drone will freeze and be made unavailable.
        While the DroneWindDecorator’s durability is 0, the drone will no longer be able to move or take pick up trips.

    Owen Liu - Data collection:
        ...


Design:

    Ben Pullis - Multi-Drone:
        **OBSERVER PATTERN**
        We wanted to keep every human automatically informed when another nearby human “publishes” an infectious event (like a sneeze) without hard‑wiring those relationships. Who is “close enough” changes every frame. Observer lets us add/remove listeners at runtime with a simple subscribe and unsubscribe instead of complicated if-else statements. This allows for looser coupling since Human doesn't need to know anything about the disease it just spread. The LeaderDrones are acting as the publisher in the observer pattern because they have a list of subscribes which are HelperDrones and whenever the LeaderDrone's battery is low it publishes a help request to all the HelperDrones which is accepted by the closest one. The HelperDrones are the subscribers because they sit idle, "observing" the Leader and waiting for a request to be sent in. The instant a HelperDrone is created it is added to the LeaderDrone's list of Helpers and there is no way for the HelperDrone to unsubscribe which is a slight modification to the normal observer pattern. This design pattern is ideal because it allows the LeaderDrone easy access to all HelperDrones enabling the LeaderDrone to quickly choose the closest HelperDrone and request assistance.
        LeaderDrone (Publishers)
            Every LeaderDrone has a list: std::vector<DroneColorDecorator*> helpers.
            When the LeaderDrone hits 20% battery it iterates through its helpers to find the closest one and sends a handoff request to that helper.
        HelperDrone (Subscribers)
            HelperDrones subscribe to LeaderDrones upon creation and can never unsubscribe. 
            The HelperDrone has two main functions, assignDelivery() and assignHandoff() that are called by the LeaderDrone whenever it needs help from a HelperDrone due to low battery.
            The assignDelivery() is for when the LeaderDrone has not picked up the package yet, in this case the Helper will both pick up and drop off the package with the same strategy as the LeaderDrone.
            The assignHandoff() is for when the LeaderDrone has already picked up the package, in this case the HelperDrone will fly to the LeaderDrone, grab the package, and finish the delivery.
        Notifications
            The LeaderDrone sends a notification when it requests a delivery. For example, "LeaderDrone low battery - Help request sent to HelperDrone-3".
            The HelperDrone sends a notification when it drops a package off like normal. It also sends a notification when a handoff is complete. For example, "HelperDrone-3 picked up package from LeaderDrone"

    
    Divyesh Thirukonda - Plague:
    
        **OBSERVER PATTERN**
        We wanted to keep every human automatically informed when another nearby human “publishes” an infectious event (like a sneeze) without hard‑wiring those relationships. Who is “close enough” changes every frame. Observer lets us add/remove listeners at runtime with a simple subscribe and unsubscribe instead of complicated if-else statements. This allows for looser coupling since Human doesn't need to know anything about the disease it just spread.
        Subjects (Publishers)
            Every Human has a list: std::vector<Human*> subscribers.
            When the human “sneezes” it calls publishDisease(), handing a copy of its current diseases to everyone in that list.
        Observers (Subscribers)
            In the main update() loop we compute the distance between every pair of humans.
            If B wanders inside A’s infection radius, we add B to A's list.
            If B wanders back out, we call unsubscribe by removing B from A's list.
        Notification
            Human::publishDisease() iterates over subscribers and invokes subscribers->receiveDisease(randomDiseaseFromMe).

        **STRATEGY PATTERN**
        Let each human decide its own acceptance logic at runtime, so we can swap behaviors like “take it as is”, “mutate it”, or “reject it.” I used the strategy pattern because of extensibility. It follows the Open/Closed principle because we can add new behaviours by adding another strategy instead of accidentally overcomplicating Human.
        Each Human owns an IReactionStrategy* reactionStrategy; and in onDiseaseReceived, we can simply choose a new random strategy, and use that strategy's processDisease() function.
            
    Adam Douiri - Severe Weather:
        ...


    Owen Liu - Data collection:
        ...


Sprint retrospective:
    The planning of this project went really well. We all knew what needed to be done for each extension. After the first sprint ended, we met up and brought some items from our backlog onto the second sprint. Communication was fluid with fast response times from every group member. We didn't have any major blockers. One thing that could be better for the Plague simulation is that spatial scanning is O(n^2), and it happens every frame. In the future, maybe we could have it update every second instead. For the Multi-Drone extension, something that could have been better was in the simulation model, I was having trouble with the type for myNewEntity whenever it was one of the drones so I had to do some funky dynamic casting to get everything to work smoothly and I feel like there is likely an easier way I could have done that. [TODO All: add some things that didn't go well with your extension]


Jira Board:
    (Add screenshots)...


UML:

    Ben Pullis - Multi-Drone:
<img src="https://i.imgur.com/qBs0yQI.png" width="800" alt="Multi-Drone UML">
    
    Divyesh Thirukonda - Plague:
    
<img src="https://i.imgur.com/ddK1NHA.png" width="800" alt="Plague UML">

    Adam Douiri - Severe Weather:
        (Add link to personal UML)...

    Owen Liu - Data collection:
        (Add link to personal UML)...
