"""
Original plan ahead, it changed somewhat along the way, and wasn't finished as the work stopped being wished for.
plan:
class: bees_game        |  function: add_creature (intrinsic + extrinsic), draw (not implemented)
                        |  fields: 2 array of intrinsic, extrinsic
~~~ any bee class, can inherit from dad class, then override growth to grow other things~~~ #todo delete, pointer, pyhtonic uneeded
class: egg              |  functions: crack (the shell), XXX      
class: Larva            |  functions: prepare_growth, XXX 
class: Pupa             |  functions: grow_to_bee, XXX 
class: bee              |  functions: eat, XXX
class: extrinsic_params |  fields: index, temperature, health, growth stage {class called - contex}
classes: Factory        |  return from dictionary new or existed instance of intrinsic class

flow:
create only one game class - singleton (didn't implement)
make sure intrinsic is immutable
then use game method in a for loop to add_creature if not existed in Factory, add extrinsic with values
Init creatures at start, queen(1), chose number of adults bee, number of eggs, larvas and pupas,
run over all creatures, check growth and other function like move, health and temperature change in night/winter etc
if new queen appear at "5" growth stage, it would kill all other queens from the list of queens,
if the sole queen too old, it would go away with 30 percent of adult bee colony.
(death event, and data movement for that (the array that hold it's data should have vacant cell... as I run through all
colony bees objects) didn't implemented currently)
"""
import sys  # convert class name as a string to object (used in Bee_lifeCycle_Factory class at init)
import numpy as np  # arrays
import random  # bees type random generator (Female, Male)
from typing import Dict  # using dictionary in Bee_lifeCycle_Factory
from typing import Union  # declare as correct input -many- types, used in Bee_lifeCycle_Factory
from dataclasses import dataclass  # immutable + a struct like behaviour
from scipy.stats import truncnorm  # used for truncated normal distribution


# todo rethink function static etc
@dataclass(frozen=True)  # Immutable, intrinsic data
class Egg:
    egg_type: str  # types are: FW, FQ, MW. Female/Male + Worker/Queen (no MQ as a male bee cannot be a Queen).

    # "cracking shell" probability get higher with higher growth value
    # return growth progress
    def cracking_shell(self, growth: float, intrinsic_factory, intrinsic_data, extrinsic_data, updating_game_map) \
            -> float:
        print("crack")
        cracking_success_result = round(random.uniform(0.1, 1), 2) * growth  # using round is faster, res has less junk
        if cracking_success_result > 2:
            intrinsic_data = intrinsic_factory.get_class_instance(self.egg_type, "Larva")  # todo check if type changes,
            # todo or because I sent cell as argument from array, it won't be as pointer, and would be immutable instead
            updating_game_map[extrinsic_data.x_coordinate][extrinsic_data.y_coordinate] = 2
            return 2  # success, apply result to extrinsic growth, and change intrinsic type to Larva
        return cracking_success_result + growth  # apply res, next time chance would be higher

    def breath_through_the_shell(self) -> None:  # todo consider delete
        print(f"A {self.egg_type} is currently processing oxygen")


@dataclass(frozen=True)  # Immutable, intrinsic data
class Larva:
    larva_type: str  # FW, FQ, MW

    # return growth progress
    def growing_fast(self, growth: float, intrinsic_factory, intrinsic_data, extrinsic_data,
                     updating_game_map) -> float:
        self.eating()
        growth_by = round(random.uniform(0.1, 1), 2) * growth
        if growth_by > 3:
            intrinsic_data = intrinsic_factory.get_class_instance(self.larva_type, "Pupa")  # todo same as egg class...
            updating_game_map[extrinsic_data.x_coordinate][extrinsic_data.y_coordinate] = 3
            return 3
        return growth_by + growth

    def eating(self) -> None:
        match self.larva_type:
            case "FQ":
                print("Behold! The larva, a future potential queen, are eating a royal jelly!")
            case "FW":
                print("a female worker is eating a worker jelly")
            case "MW":
                print("a male worker is eating a drone jelly")
            case _:
                print("wrong naming! <(#_*)> check out what happened (at larva eating func)")


@dataclass(frozen=True)  # Immutable, intrinsic data
class Pupa:
    pupa_type: str  # FW, FQ, MW

    def pupa_action(self) -> None:
        print("Spin a cocoon around itself and pupate, "
              "then, it develops into a recognisable bee, with wings, legs, head, thorax and abdomen")

    # return growth progress
    def pupa_growth(self, growth: int, intrinsic_factory, intrinsic_data, extrinsic_data, updating_game_map) -> float:
        growth_by = round(random.uniform(0.1, 1), 2) * growth
        if growth_by > 4:
            intrinsic_data = intrinsic_factory.get_class_instance(self.pupa_type, "Bee")  # todo same, a check needed..
            updating_game_map[extrinsic_data.x_coordinate][extrinsic_data.y_coordinate] = 4
            return 4
        return growth_by + growth


@dataclass(frozen=True)  # Immutable, intrinsic data
class Bee:
    bee_type: str  # 3 options

    def eat(self, growth: int) -> float:  # return growth stage #todo check get map, queen list extrinsic, intrinsic etc
        match growth:  # todo use move functionality, apply to map with check if grid moving to is free
            case 4:
                print(f"a young adult {self.bee_type} emerging from the hexagonal-shaped egg cell,"
                      " by chewing its way through the wax capping.")
                return 5  # todo change map, apply growth
            case 5:
                if self.bee_type == "FQ":
                    print("Behold! The queen are eating a royal jelly!")
                    # todo check stage+type to use "lay_eggs"(if not winter currently), save index,
                    #  kill other queens if not too old
                    #  return older new queen pointer
                    #  if queen old - no eggs, stop killing queens, grow new queens... after new adult queen appeared,
                    #   old would take 30 percent from colony and move away
                    return 6  # apply 6 to growth, kill other queens todo
                print("a bee is eating a nectar or a pollen")
                return 6  # apply to growth extrinsic factor

            # death chance grow with the bee, calculated outside with more extrinsic data # todo
            # if growth higher than 6: (case _: is default, so it can get e.g. 0, but by program logic it shouldn't).
            case _:
                if growth < 15:
                    return 0.1 * growth + growth  # apply to extrinsic growth
                return 15  # bee dies, if a bee queen, dev more queens. todo


def move():  # static func as no need to create potential 10M funcs in extrinsic objects doing the same - choosing a way
    move_to = np.random.randint(0, 8, size=None)  # 8 movement options
    return move_to  # todo consider using without func, one line...@@@###


@dataclass
class extrinsic_params:  # easily get and set vals.
    x_coordinate: int
    y_coordinate: int
    health: float
    growth: float
    temperature_resistance: float
    id: int


class Bee_lifeCycle_Factory:
    """
    When the client requests a flyweight (intrinsic class data),
    the factory either returns an existing instance ("pointer"), or creates a new one if it doesn't exist yet.
    """

    _Bee_lifeCycle: Dict[str, Union[Egg, Larva, Pupa, Bee]] = {}

    # class_types: FQ, FW, MW. class_indicator: 0, 1, 2, 3 = egg, larva, pupa, bee
    def __init__(self, field_types: list, classes_name: list) -> None:
        for list_set_ind, class_name in enumerate(classes_name):
            for field_type in field_types[list_set_ind]:
                self._Bee_lifeCycle[self.get_key(field_type, class_name)] = self.str_to_class(class_name)(field_type)

    def str_to_class(self, class_name):
        return getattr(sys.modules[__name__], class_name)

    # create dictionary key with class name + field
    def get_key(self, field_type: str, class_type: str) -> str:
        """
        Returns a Flyweight's string hash for a given state.
        """
        return "_".join(sorted([field_type, class_type]))

    def get_class_instance(self, field_type: str, class_name: str) -> Union[Bee, Larva, Egg, Pupa]:
        """
        Returns an existing Flyweight with a given state or creates a new one.
        """
        # todo count all prints per minutes and showing once instead of showing all, would run faster
        key = self.get_key(field_type, class_name)
        if field_type == "FQ" or field_type == "FW" or field_type == "MW":
            if not self._Bee_lifeCycle.get(key):
                print(f"FlyweightFactory: Can't find {class_name} class with \"{field_type}\" "
                      f"as its field, creating a new one.")
                self._Bee_lifeCycle[key] = self.str_to_class(class_name)(field_type)
            else:
                print("FlyweightFactory: Reusing existing class instance.")
            return self._Bee_lifeCycle[key]
        else:
            print(f"{field_type} is a wrong field type. It should be one option from these: FW, MW, FQ.")
            exit(1)

    def list_classes(self) -> None:
        count = len(self._Bee_lifeCycle)
        print(f"bee_classes_Factory: I have {count} classes:")
        print("\n".join(map(str, self._Bee_lifeCycle.keys())), end="")


# main class, hold all the data except the factory objects of intrinsic state, todo maybe add here?
class Bees_Game:
    # initiation:
    def __init__(self,
                 intrinsic_extrinsic: np.array,
                 queens_coordinate: list,
                 game_map: np.array,
                 colony_init_num: int,
                 intrinsic_factory: Bee_lifeCycle_Factory):
        # Extrinsic: x_coordinate, y_coordinate, curr_temperature, health, growth stage, temperature_resistance, id.
        # Intrinsic: gender(M,F) + type(worker\queen) no M+Queen!

        self.intrinsic_extrinsic = intrinsic_extrinsic
        self.game_map = game_map
        self.queens_coordinate = queens_coordinate
        self.colony_current_num = colony_init_num  # upper bounder in the for loop (run the game func)
        self.bee_Id = colony_init_num  # any new creation of bees, updated todo
        self.intrinsic_factory = intrinsic_factory  # using factory during the game to get existing instance or create.

    # upon queen lay eggs: #todo, use bee id as needed
    def add_eggs_layed_by_queen(self, specific_data, generic_data) -> None:  # (intrinsic, extrinsic)
        pass  # todo didn't implemented
        # np.concatenate([self.intrinsic, specific_data])
        # np.concatenate([self.extrinsic, generic_data])

    def delete_list_of_creatures_upon_death(self, lst_del) -> None:
        # todo add search by index as input list,
        #  or map should have a pointer per x,y index to extrinsic val
        pass  # todo didn't implemented
        # np.delete(self.intrinsic, lst_del)
        # np.delete(self.extrinsic, lst_del)

    def run_the_game(self):
        while True:  # todo add user stop option (not a must)
            for ind_filled_objects in range(self.colony_current_num):
                # switch case run faster than inheritance (tested at run_time_check.py):
                match type(self.intrinsic_extrinsic[ind_filled_objects][0]).__name__:
                    case "Egg":
                        additional_egg_growth = self.intrinsic_extrinsic[ind_filled_objects][0].cracking_shell(
                            self.intrinsic_extrinsic[ind_filled_objects][1].growth,  # update growth using current
                            self.intrinsic_factory,  # used if next stage achieved to change intrinsic
                            # todo check pointer and not immutable (line below)
                            self.intrinsic_extrinsic[ind_filled_objects][0],  # intrinsic exact cell pointer..
                            self.intrinsic_extrinsic[ind_filled_objects][1],  # extrinsic,using x,y values to update map
                            self.game_map  # updated if needed
                        )
                        # (temperature irrelevant here, as eggs doesn't being laid in the winter).
                        self.intrinsic_extrinsic[ind_filled_objects][1].growth = additional_egg_growth
                    case "Larva":  # todo add temperature change event applying to growth, from .8-1.2 temp multi growth
                        additional_larva_growth = self.intrinsic_extrinsic[ind_filled_objects][0].growing_fast(
                            self.intrinsic_extrinsic[ind_filled_objects][1].growth,
                            self.intrinsic_factory,
                            self.intrinsic_extrinsic[ind_filled_objects][0],  # todo check pointer and not immutable
                            self.intrinsic_extrinsic[ind_filled_objects][1],  # x,y values to update map
                            self.game_map  # updated if needed
                        )
                        self.intrinsic_extrinsic[ind_filled_objects][1].growth = additional_larva_growth
                    case "Pupa":  # todo add temperature change event applying to growth, from .8-1.2 temp multi growth.
                        additional_pupa_growth = self.intrinsic_extrinsic[ind_filled_objects][0].pupa_growth(
                            self.intrinsic_extrinsic[ind_filled_objects][1].growth,
                            self.intrinsic_factory,
                            self.intrinsic_extrinsic[ind_filled_objects][0],  # todo check pointer and not immutable
                            self.intrinsic_extrinsic[ind_filled_objects][1],  # x,y values to update map
                            self.game_map)  # updated if needed
                        self.intrinsic_extrinsic[ind_filled_objects][1].growth = additional_pupa_growth
                    case "Bee":  # todo stopped here...
                        additional_bee_growth = self.intrinsic_extrinsic[ind_filled_objects][0].eat(
                            self.intrinsic_extrinsic[ind_filled_objects][1].growth)
                        self.intrinsic_extrinsic[ind_filled_objects][1].growth = additional_bee_growth

                    case _:
                        print("wrong naming! <(#_*)> check out what happened. (at run the game func)")

    def draw(self):
        currently_not_implemented = -1  # can be implemented using canvas, or pygame of some pixels


def extrinsic_params_generator(game_map_matrix: np.array, map_length: int, class_name: str,
                               id: int) -> extrinsic_params:
    """ # a reminder for extrinsic params:
    x_coordinate: int =>
    y_coordinate: int => random (x_coordinate, y_coordinate) while coo'!= -1 (as map init to -1 each cell)
    temperature_resistance : float => didn't implement temperature change, but using winter and summer to move from 0.8
    to 1.2 temperature and down to change growth rate, and determine if bee queen would lay eggs
    (as it doesn't happen in winter), should implement a temperature func, using resistance + health applied to growth
                        # strategy: higher resistance, health won't change much, growth would slow only a little bit...
    health      : float # 1-10, higher goes to healthy. lower => higher growth ("growing old", closer to death faster)
                # death wasn't implemented
    growth      : float # egg: 0-2, larva: 2-3, pupa: 3-4, bee: 5-15, 15=too old, death
    id          : bee id => int from 0 and up
    """
    # generating coordinates per object
    x = random.randint(0, map_length)  # get random integer in range 0->3999 included
    y = random.randint(0, map_length)
    while game_map_matrix[x][y] != -1:
        x = random.randint(0, map_length)
        y = random.randint(0, map_length)
    growth = 1
    match class_name:
        case "Egg":
            game_map_matrix[x][y] = 1
        case "Larva":
            game_map_matrix[x][y] = growth = 2
        case "Pupa":
            game_map_matrix[x][y] = growth = 3
        case "Bee":
            game_map_matrix[x][y] = growth = 4
        case _:
            print("wrong naming! <(#_*)> check out what happened (at extrinsic params generator)")

    # high resistance at 9+, lowest at 0+, weather affecting health, affecting death.
    def get_truncated_normal(mean=0, sd=1, low=0, upp=10):
        return truncnorm((low - mean) / sd, (upp - mean) / sd, loc=mean, scale=sd)

    # todo if at runtime a need arise to run the program faster, change to normal instead of truncated (much faster)
    temperature_resistance = get_truncated_normal(mean=5, sd=1, low=1, upp=9).rvs()
    health = np.random.uniform(low=0.1, high=10)  # todo chance to death + growth is lower the higher the health.
    return extrinsic_params(x, y, round(health, 2), growth, round(temperature_resistance, 2), id)


def create_init_intrinsic_and_extrinsic_data(intrinsic_factory: Bee_lifeCycle_Factory,
                                             variation_per_class_lst: list,
                                             egg_init: int,
                                             larva_init: int,
                                             pupa_init: int,
                                             bee_init: int,
                                             init_overall_num: int) -> np.array:
    """ Flow:
    using np array to hold per object intrinsic + extrinsic data, while extrinsic (x,y) applied to map of 16M cells.
    Objects are randomly placed (probability of falling to same cell or low enough... otherwise could use list indices
    + remove).
    """
    num_columns = 2  # first col for extrinsic, sec col for intrinsic

    # rows length: choosing a starting colony capacity with "space"(>init num) for colony growth
    # (np append create a new array with copied values, so I add space to avoid using append, but not too much
    # if not needed to not use unneeded memory unnecessarily).
    if init_overall_num < 1000:
        num_rows = 100000
    elif 1000 < init_overall_num < 10000:
        num_rows = 1000000
    else:
        num_rows = 10000000

    # extrinsic + intrinsic data:
    ex_in_array = np.array([[0 for i in range(2)] for j in range(num_rows)], dtype=object)  # todo to globally in class

    # map boundaries: assuming max colony num is 10000000, hence map would be 4000*4000, which is higher
    #                 than max num (10000000) sqrt... that way I get some "moving space" for sure.
    map_size = 4000
    game_map_matrix = np.array([[-1 for i in range(map_size)] for j in range(map_size)])
    # could use here a mat in the same shape of map above, to remove each chosen place, but as I have enough space by
    # design, "expected value" should be ok even-thought it might fall to the same place more than once...
    # map indices = 16M, max colony = 10M, hence 9999999/16m=0.62, good enough.

    queen_lst_coordinates = []  # further use to determine queen and more
    # add intrinsic + extrinsic data to first and second column respectively

    # Eggs init, add to array, add to map, add FQ if exist to lst, same for other classes.
    for bee_ind in range(egg_init):
        ex_in_array[bee_ind][0] = intrinsic_factory.get_class_instance(variation_per_class_lst[bee_ind], "Egg")
        ex_in_array[bee_ind][1] = extrinsic_params_generator(game_map_matrix, map_size - 1, "Egg", bee_ind)
        if variation_per_class_lst[bee_ind] == "FQ":
            queen_lst_coordinates.append([ex_in_array[bee_ind][1].x_coordinate, ex_in_array[bee_ind][1].y_coordinate])

    # Larva:
    for bee_ind in range(egg_init, egg_init + larva_init):
        ex_in_array[bee_ind][0] = intrinsic_factory.get_class_instance(variation_per_class_lst[bee_ind], "Larva")
        ex_in_array[bee_ind][1] = extrinsic_params_generator(game_map_matrix, map_size - 1, "Larva", bee_ind)
        if variation_per_class_lst[bee_ind] == "FQ":
            queen_lst_coordinates.append([ex_in_array[bee_ind][1].x_coordinate, ex_in_array[bee_ind][1].y_coordinate])

    # Pupa
    for bee_ind in range(egg_init + larva_init, egg_init + larva_init + pupa_init):
        ex_in_array[bee_ind][0] = intrinsic_factory.get_class_instance(variation_per_class_lst[bee_ind], "Pupa")
        ex_in_array[bee_ind][1] = extrinsic_params_generator(game_map_matrix, map_size - 1, "Pupa", bee_ind)
        if variation_per_class_lst[bee_ind] == "FQ":
            queen_lst_coordinates.append([ex_in_array[bee_ind][1].x_coordinate, ex_in_array[bee_ind][1].y_coordinate])

    # Bee
    for bee_ind in range(pupa_init + egg_init + larva_init, egg_init + larva_init + pupa_init + bee_init):
        ex_in_array[bee_ind][0] = intrinsic_factory.get_class_instance(variation_per_class_lst[bee_ind], "Bee")
        ex_in_array[bee_ind][1] = extrinsic_params_generator(game_map_matrix, map_size - 1, "Bee", bee_ind)
        if variation_per_class_lst[bee_ind] == "FQ":
            queen_lst_coordinates.append([ex_in_array[bee_ind][1].x_coordinate, ex_in_array[bee_ind][1].y_coordinate])

    return ex_in_array, queen_lst_coordinates, game_map_matrix


if __name__ == "__main__":

    # init game numbers:

    correct_input = False
    ans = input("Please choose d for default arguments, or u for user arguments: ")
    while not correct_input:
        match ans:
            case "d":
                egg_num = 10  # todo consider change naming from egg to eggs_init_number etc, not a must...
                larva_num = 10
                pupa_num = 10
                bee_num = 10
                correct_input = True
            case "u":
                print("Please notice that overall number should be from 30 to 10M")
                try:
                    egg_num = abs(
                        int(input("Please choose from 0 and up, how many eggs the game would start with:   ")))
                    larva_num = abs(
                        int(input("Please choose from 0 and up, how many larvas the game would start with: ")))
                    pupa_num = abs(
                        int(input("Please choose from 0 and up, how many pupas the game would start with:  ")))
                    bee_num = abs(
                        int(input("Please choose from 0 and up, how many bees the game would start with:   ")))
                    correct_input = True
                except ValueError:
                    # The cycle will go on until validation
                    print("Error! This is not a number. Try again.")
            case _:
                print("Wrong input, please write u or d as an answer.")
                ans = input("A reminder, d stands for default arguments, u stands for user arguments.")

    #  sum to generate the random, and chose how many queens (up to 20), to develop
    colony_init_num = egg_num + larva_num + pupa_num + bee_num

    # options:
    bee_type_options = ["FW", "MW"]  # Female Worker, Male Worker
    # check how many queens are appropriate to develop
    if colony_init_num > 1000:
        bees_variation = [random.choice(bee_type_options) for _ in range(colony_init_num - 20)]
        bees_variation += ["FQ" for i in range(20)]
    elif 29 < colony_init_num <= 1000:
        bees_variation = [random.choice(bee_type_options) for _ in range(colony_init_num - 3)]
        bees_variation += ["FQ" for i in range(3)]
    else:
        print("\nPlease choose a higher starting population (+30) at initiation")
        exit(1)
    random.shuffle(bees_variation)  # shuffling queens positions, relevant to factory init creation

    # checking init factory types per class
    egg_num_factory_types = set(bees_variation[0:egg_num])
    larva_num_factory_types = set(bees_variation[egg_num: egg_num + larva_num])
    pupa_num_factory_types = set(bees_variation[egg_num + larva_num: egg_num + larva_num + pupa_num])
    bee_num_factory_types = set(
        bees_variation[egg_num + larva_num + pupa_num: egg_num + larva_num + pupa_num + bee_num])

    # prepare data input to factory
    lst_set_classes_types = [egg_num_factory_types, larva_num_factory_types, pupa_num_factory_types,
                             bee_num_factory_types]
    classes_names = ["Egg", "Larva", "Pupa", "Bee"]

    # init factory object:
    intrinsic_data_factory = Bee_lifeCycle_Factory(lst_set_classes_types, classes_names)

    """ # Usage example:
    a = intrinsic_data_factory.get_class_instance("FQ", "Egg")  # Reusing existing class instance/creating new instance
    b = intrinsic_data_factory.get_class_instance("MQ", "Bee")  # Wrong type
    
    # showing all intrinsic "saved" classes in init:
    intrinsic_data_factory.list_classes()
    """

    # init game starting data by creating extrinsic data per intrinsic
    intrinsic_extrinsic_arr, queens_coordinates, game_map = \
        create_init_intrinsic_and_extrinsic_data(intrinsic_data_factory,
                                                 bees_variation,
                                                 egg_num,
                                                 larva_num,
                                                 pupa_num,
                                                 bee_num,
                                                 colony_init_num)

    game = Bees_Game(intrinsic_extrinsic_arr, queens_coordinates, game_map, colony_init_num, intrinsic_data_factory)
    game.run_the_game()

    # todo add listener dp to temperature change...
    # todo add singleton to game class, and to factory class
    # todo death and birth while saving array filled without holes...
    # apply move for all objects in run the game vs check in map if available (if randomly want to move to grid with -1)
    # todo upon creating new bees, use bees counter id inside run the game app using game counter field and update it
    #  upon laid/death event
    # todo add threads to make it all run much faster, e.g. thread per class at init, print aggregated printing data
    #  using thread instead of stopping prog for I/O etc
    # todo clean code, utility.py, classes.py shorten etc...
