Team Number: 010-25


Team Names: 
    Ben Pullis - pulli068, Divyesh Thirukonda - thiru063, Adam Douiri - douir002, Owen Liu - liu02753

Docker:
    https://hub.docker.com/r/devadamd/final_project

Overview: 
    This project is a drone delivery simulation written primarily in C++. The user can interact with the simulation by adding a source and destination for the drone to deliver its package. To make the simulation more realistic and lively, we added entities such as a human, helicopter, and robots. There is also a notification panel with important information passed through it. With our latest additions, humans can get sick and spread their diseases with each other. HelperDrones can assist in deliveries whenever a LeaderDrone is low on battery. There is a wind system that applies wind to Drones in the air and does damage to the Drones until they are unusable. [TODO Owen: describe your additions in one sentence]


Instructions:

    If running locally:
    Build: "make clean; make -j"
    Run: "make run"
    
    If using Docker:
    Fetch: docker pull devadamd/final_project
    Build: docker build -t devadamd/final_project .
    Run: run "docker run --rm -it -p hostport:containerport devadamd/final_project", where hostport and containerport are the ports you want to run the simulation on (recommended that both are 8081).
    
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
    Data Collection:
    	When you open the simulation, add a couple of humans, and start looking at ExportCSV.csv. 
        Once the file is updated, you can continue to add more entities, and also experiment with the toggle button to pause updating.
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
        If a Drone hits 0 durability while delivering a package, then the package shall be readded to the delivery scheduler to be picked up by another Drone.

    Owen Liu - Data collection:
        The (Data Collection Manager) Object shall log the postion of the entities and names.
    	While the simulation is active, the update thread will update every 10 milliseconds
    	While an entity is updated by the SimulationModel, the Data Collection Manager will check if it has not been stored/monitored yet
    	If an entity is destroyed or cannot be reached, then the Data Collection Manager will not track it further.
    	The Manager shall export its data in a human-readable and parsable CSV.
    	The manager shall internally store its data with a Map, where its key is the Entity and value is a custom struct.
    	The custom struct shall contain a position vector and a string name.
    	If the user toggles by clicking the toggle button, then the Object will not export until toggled again.

        ...


Design:

    Ben Pullis - Multi-Drone:
        **OBSERVER PATTERN**
        The LeaderDrones are acting as the publisher in the observer pattern because they have a list of subscribes which are HelperDrones and whenever the LeaderDrone's battery is low it publishes a help request to all the HelperDrones which is accepted by the closest one. The HelperDrones are the subscribers because they sit idle, "observing" the Leader and waiting for a request to be sent in. The instant a HelperDrone is created it is added to the LeaderDrone's list of Helpers and there is no way for the HelperDrone to unsubscribe which is a slight modification to the normal observer pattern. This design pattern is ideal because it allows the LeaderDrone easy access to all HelperDrones enabling the LeaderDrone to quickly choose the closest HelperDrone and request assistance.
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
    
        **SINGLETON PATTERN**
        The SevereWeatherSystem class implements the Singleton Design Pattern. The reason for making the SevereWeatherSystem class a Singleton is that we want to have a singular wind gust for the entire simulation. In real life, wind gusts in that small of an area are not going to be in different directions depending on the area (at least high up in the air). 
        This choice also helps protect the S of SOLID, since we totally could have implemented the wind generation in something like SimulationModel.cc. By using a Singleton, we adhere to the Single Responsibility Principle.
        
        **DECORATOR PATTERN**
        The DroneWindDecorator class implements the Decorator Design Pattern. Overall, this design pattern proved to be beneficial in almost all SOLID principles. The first reason for using the Decorator pattern is primarily to adhere to the O of SOLID, and this was rather successful. The usage of the Decorator allowed me to implement my extension with very little changes to other classes. 
        When it came time to integrate my extension, the choice of a Decorator helped significantly with the L of SOLID. Had I directly implemented the extension to Drone.cc, it is very likely we would have ran into a lot more errors when integrating into Ben's Leader/Helper drone extension, which would have then inherited from an edited Drone.cc. Introducing a Decorator made integration quite smooth and avoided violating the L of SOLID.
        Another big benefit was that we avoided violating the S of SOLID. If I directly implemented my extension into Drone.cc, the Drone class simply would be doing too much. By making my own decorator, the responsibilities of the classes are clearly seperate. 
        I did consider that having only one decorator did not perfectly adhere to the Single Responsibility Principle, but after trying to make a second decorator I realized that would be an unwise design choice for two reasons. First, this would be likely to violate the O and L of SOLID, as this would create a more complex Decorator wrapping chain, requiring serious refactoring of existing classes. Second, this seemed like unneccessary bloat for the project, as the .cc file of the seperate Decorator was only a few lines long. As it stands DroneWindDecorator.cc is not long at all, and does have a single responsibility in managing the response to wind, so I believe I did my best with that.



    Owen Liu - Data collection:
    **SINGLETON PATTERN**
    	The object Datam, implemented in the code as Datama, is a singleton, as a Data collection manager should only have 1 instance. This way, there shouldn't be multiple instances and copies of collections active in a simulation, causing massively slower code and risking heap smashing, which is an example of the Single Responsibility Principle of SOLID Software Design.
    	Implementing a Singleton also allowed separating updates for updating to a file. This separation of design allows for future refactoring to be easy, as Datam.h and Datam.cc are responsible for their own cycle of updating ExportCSV.cc
    	I did implement a design where exporting/managing file data was in a single object, but this was purposefully done in order to make the point of my Data collection manager clearer. Although this possibly violated a design principle, it decreased code smell for future extensions to work off of it.

        ...


Sprint retrospective:
    The planning of this project went really well. We all knew what needed to be done for each extension. After the first sprint ended, we met up and brought some items from our backlog onto the second sprint. Communication was fluid with fast response times from every group member. We didn't have any major blockers. One thing that could be better for the Plague simulation is that spatial scanning is O(n^2), and it happens every frame. In the future, maybe we could have it update every second instead. For the Multi-Drone extension, something that could have been better was in the simulation model, I was having trouble with the type for myNewEntity whenever it was one of the drones so I had to do some funky dynamic casting to get everything to work smoothly and I feel like there is likely an easier way I could have done that. For the Severe Weather System, I would say something that could have definitely went better would be confirming my requirements earlier. There were a few requirements in the final project write-up that were rather ambiguous that I didn't get 100% confirmation on, that I ended up only asking about after my initial implementation. Luckily, they were not hard to implement at all, but I could totally have seen that being very stressful had I neglected some other, more integral requirement. I think what really went well for the Severe Weather System was integration. Ben and I really put thought into our integration well before we actually did it. We consulted Shonal about our integration in a timely manner giving us a lot of time to plan ahead.   [TODO All: add some things that didn't go well with your extension]


Jira:

    Sprint 1:
<img src="https://i.imgur.com/906VWhl.png" width="800" alt="Multi-Drone UML">

    Sprint 2:
<img src="https://i.imgur.com/TCafJDZ.png" width="800" alt="Multi-Drone UML">


UML:

    Ben Pullis - Multi-Drone:
<img src="https://i.imgur.com/buwSyAZ.png" width="800" alt="Multi-Drone UML">
    
    Divyesh Thirukonda - Plague:
    
<img src="https://i.imgur.com/ddK1NHA.png" width="800" alt="Plague UML">

    Adam Douiri - Severe Weather:
<img src="https://i.imgur.com/ew6yebu.png" width="800" alt="Severe Weather UML">

    Owen Liu - Data collection:
<img src="https://i.imgur.com/Jnsoj4r.png" width="800" alt="Data Collection UML">

