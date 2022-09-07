"""
Original plan ahead, it changed somewhat along the way, and wasn't finished to my best capabilities, but its pretty good as example of Flyweight DP.
plan:
class: bees_game        |  function: add_creature (intrinsic + extrinsic), draw (not implemented)
                        |  fields: 2 array of intrinsic, extrinsic
~~~ any bee class, can inherit from dad class, then override growth to grow other things~~~
todo delete line above, using pointer, pythonic way, inheritance is unneeded, as it run slower, been tested
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


@dataclass(frozen=True)  # Immutable, intrinsic data
class Egg:
    egg_type: str  # types are: FW, FQ, MW. Female/Male + Worker/Queen (no MQ as a male bee cannot be a Queen).

    # "cracking shell" probability get higher with higher growth value
    # return growth progress, and change intrinsic object if growth stage passed the threshold
    def cracking_shell(self, growth: float, intrinsic_factory, int_extrinsic_data, egg_indx, updating_game_map) \
            -> float:
        print("crack")
        cracking_success_result = round(random.uniform(0.1, 1), 2) * growth  # using round is faster, res has less junk
        if cracking_success_result > 2:
            int_extrinsic_data[egg_indx][0] = intrinsic_factory.get_class_instance(self.egg_type, "Larva")
            updating_game_map[int_extrinsic_data[egg_indx][1].x_coordinate][
                int_extrinsic_data[egg_indx][1].y_coordinate] = 2
            return 2  # success, apply result to extrinsic growth, and change intrinsic type to Larva
        return cracking_success_result + growth  # apply res, next time chance would be higher

    def breath_through_the_shell(self) -> None:
        # todo consider delete, or use action for bee queen movement checking
        #  for its colony citizens action, a "meet" event...
        #  maybe change all action func (for all extrinsic class) to the same name (action) for easier usage instead of
        #  switch case
        print(f"A {self.egg_type} is currently processing oxygen")


@dataclass(frozen=True)  # Immutable, intrinsic data
class Larva:
    larva_type: str  # FW, FQ, MW

    # return growth progress
    def growing_fast(self, growth: float, intrinsic_factory, int_extrinsic_data, larva_indx,
                     updating_game_map) -> float:
        self.eating()
        growth_by = round(random.uniform(0.1, 1), 2) * growth
        if growth_by > 3:
            int_extrinsic_data[larva_indx][0] = intrinsic_factory.get_class_instance(self.larva_type, "Pupa")
            updating_game_map[int_extrinsic_data[larva_indx][1].x_coordinate][
                int_extrinsic_data[larva_indx][1].y_coordinate] \
                = 3
            return 3
        return growth_by + growth

    def eating(self) -> None:
        match self.larva_type:
            case "FQ":
                print("Behold! The larva, a future potential queen, is eating a royal jelly!")
            case "FW":
                print("a female worker is eating a worker jelly")
            case "MW":
                print("a male worker is eating a drone jelly")
            case _:
                print("wrong naming! <(#_*)> check out what happened (at larva eating func)")


@dataclass(frozen=True)  # Immutable, intrinsic data
class Pupa:
    pupa_type: str  # FW, FQ, MW

    # return growth progress
    def pupa_growth(self, growth: int, intrinsic_factory, int_extrinsic_data, pupa_indx, updating_game_map) -> float:
        growth_by = round(random.uniform(0.1, 1), 2) * growth
        if growth_by > 4:
            int_extrinsic_data[pupa_indx][0] = intrinsic_factory.get_class_instance(self.pupa_type, "Bee")
            updating_game_map[int_extrinsic_data[pupa_indx][1].x_coordinate][
                int_extrinsic_data[pupa_indx][1].y_coordinate] \
                = 4
            return 4
        self.pupa_action()
        return growth_by + growth

    def pupa_action(self) -> None:
        print(f"A young {self.pupa_type} spin a cocoon around itself and pupate, "
              "then, it develops into a recognisable bee, with wings, legs, head, thorax and abdomen")


@dataclass(frozen=True)  # Immutable, intrinsic data
class Bee:
    bee_type: str  # FW, FQ, MW

    # return growth stage, change object intrinsic if growth passed the threshold
    def eat(self, growth: int, int_extrinsic_data, bee_indx, updating_game_map, eggs_lay_func) -> float:
        match growth:
            case 4:
                print(f"a young adult {self.bee_type} emerging from the hexagonal-shaped egg cell,"
                      " by chewing its way through the wax capping.")
                updating_game_map[int_extrinsic_data[bee_indx][1].x_coordinate]\
                    [int_extrinsic_data[bee_indx][1].y_coordinate] = 5
                return 5
            case 5:
                if self.bee_type == "FQ":
                    print("Behold! The queen is eating a royal jelly!")
                    # todo check stage + type to use "lay_eggs"(if not winter currently), save index,
                    #  kill other queens if not too old, use death functionality in Game class to fill the holes
                    #  return older new queen pointer
                    #  if queen old - no eggs, stop killing queens, grow new queens... after new adult queen appeared,
                    #   old would take 30 percent from colony and move away, by old, lets say > 10

                    # no reason IMO by run time rational
                    # to check twice (+1 outside eat func) is bee at 5 and up stage and capable of moving
                    move(updating_game_map, int_extrinsic_data, bee_indx)
                    # todo in thread, btw, I dont care that much if 2 bees would fall to the very
                    #  same grid (as can be in nature) if working with threads...
                    today_i_will_be = random.choice(["laying_eggs", "lazy"])
                    if today_i_will_be != "lazy":
                        eggs_lay_func()
                    # todo: kill all queen below age 10,
                    #  open thread to work per 1 minute(?) to lay eggs, and grow slowly, check age,
                    #  if age > 9 stop killing queens, laying eggs until age = 10, kill threads
                    #  if colony at 70% filled and up, old queen take 30% colony away
                    return 6  # apply 6 to growth

                print("a bee is eating a nectar or a pollen")
                move(updating_game_map, int_extrinsic_data, bee_indx)
                return 6  # apply to growth extrinsic factor

            # death chance grow with the bee, calculated outside with more extrinsic data # todo
            # if growth higher than 6: (case _: is default, so it can get e.g. 0, but by program logic it shouldn't).
            case _:
                if growth < 15:
                    updating_game_map[int_extrinsic_data[bee_indx][1].x_coordinate] \
                        [int_extrinsic_data[bee_indx][1].y_coordinate] = growth
                    move(updating_game_map, int_extrinsic_data, bee_indx)
                    return 0.1 * growth + growth  # apply to extrinsic growth
                # else, not moving anymore...
                return 15  # bee dies, if a bee queen, dev more queens.
                # todo add object index to death list, at end, run, change map to -1, than fill gaps in ex_intrinsic arr
                #  (should have been more potential queens way before 15 stage) todo


def move(updating_game_map, int_extrinsic_data, bee_ind) -> None:
    """
    random choice movement meaning:
    0 = up           map index meaning:       y-=1
    1 = top right    map index meaning: x+=1, y-=1
    2 = right        map index meaning: x+=1,
    3 = button right map index meaning: x+=1, y+=1
    4 = button       map index meaning:       y+=1
    5 = button left  map index meaning: x-=1, y+=1
    6 = left         map index meaning: x-=1,
    7 = top left     map index meaning: x-=1, y-=1
    If at first try, grid is taken (not = -1), bee won't move for current whole colony actions (current for loop...)
    an option, to use list with 8 options, and remove each "move" option (that point to a not free greed) from random
    option, if empty, object won't move. As map big enough, and movement isn't that important, only one try per object.
    """
    move_to = np.random.randint(0, 8, size=None)  # 8 movement options - (0 to 7).
    x_coor = int_extrinsic_data[bee_ind][1].x_coordinate
    y_coor = int_extrinsic_data[bee_ind][1].y_coordinate
    match move_to:  # todo a border check + grid coordinates meaning - probably (0,0) at top left, x+ goes right,y+ down
        case 0:
            if -1 != updating_game_map[x_coor][y_coor - 1]:
                updating_game_map[x_coor][y_coor - 1] = int_extrinsic_data[bee_ind][1].growth
                updating_game_map[x_coor][y_coor] = -1
            return
        case 1:
            if -1 != updating_game_map[x_coor + 1][y_coor - 1]:
                updating_game_map[x_coor + 1][y_coor - 1] = int_extrinsic_data[bee_ind][1].growth
                updating_game_map[x_coor][y_coor] = -1
            return
        case 2:
            if -1 != updating_game_map[x_coor + 1][y_coor]:
                updating_game_map[x_coor + 1][y_coor] = int_extrinsic_data[bee_ind][1].growth
                updating_game_map[x_coor][y_coor] = -1
            return
        case 3:
            if -1 != updating_game_map[x_coor + 1][y_coor + 1]:
                updating_game_map[x_coor + 1][y_coor + 1] = int_extrinsic_data[bee_ind][1].growth
                updating_game_map[x_coor][y_coor] = -1
            return
        case 4:
            if -1 != updating_game_map[x_coor][y_coor + 1]:
                updating_game_map[x_coor][y_coor + 1] = int_extrinsic_data[bee_ind][1].growth
                updating_game_map[x_coor][y_coor] = -1
            return
        case 5:
            if -1 != updating_game_map[x_coor - 1][y_coor + 1]:
                updating_game_map[x_coor - 1][y_coor + 1] = int_extrinsic_data[bee_ind][1].growth
                updating_game_map[x_coor][y_coor] = -1
            return
        case 6:
            if -1 != updating_game_map[x_coor - 1][y_coor]:
                updating_game_map[x_coor - 1][y_coor] = int_extrinsic_data[bee_ind][1].growth
                updating_game_map[x_coor][y_coor] = -1
            return
        case 7:
            if -1 != updating_game_map[x_coor - 1][y_coor - 1]:
                updating_game_map[x_coor - 1][y_coor - 1] = int_extrinsic_data[bee_ind][1].growth
                updating_game_map[x_coor][y_coor] = -1
            return
        case _:
            print("move func, random option went wrong"), exit(1)
    return  # unneeded?


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
        # todo sum all prints per minutes and showing once instead of showing all, would run much faster
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


# game class, holds all the needed data to run the game
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

    # adult bee queen lay eggs
    def add_eggs_laid_by_queen(self) -> None:  # (intrinsic, extrinsic)
        if self.colony_current_num < 8900000:
            added_eggs_num = int(self.colony_current_num * 0.1)
            end = self.colony_current_num + added_eggs_num
            for added_egg_id in range(self.colony_current_num, end):
                #  a better approach might insert eggs into vacant cell left by bees death todo
                # todo check ind numbers is ok (line below)
                self.intrinsic_extrinsic[added_egg_id][0] \
                    = self.intrinsic_factory.get_class_instance(random.choice(["FW", "MW"]), "Egg")  # todo func only for eggs, would be faster
                self.intrinsic_extrinsic[added_egg_id][1] = extrinsic_params_generator(self.game_map, len(self.game_map) - 1, "Egg", added_egg_id)

            # add one queen egg, (can do random quantity, todo)
            self.intrinsic_extrinsic[self.colony_current_num + added_eggs_num][0] \
                = self.intrinsic_factory.get_class_instance("FQ", "Egg")
            self.intrinsic_extrinsic[self.colony_current_num + added_eggs_num][1] \
                = extrinsic_params_generator(self.game_map, len(self.game_map) - 1, "Egg", self.bee_Id+added_eggs_num+1)
            self.queens_coordinate.append([self.intrinsic_extrinsic[end][1].x_coordinate,
                                           self.intrinsic_extrinsic[end][1].y_coordinate])  # adding to queens lst

            self.colony_current_num += added_eggs_num + 1
        self.bee_Id += added_eggs_num + 1
        return

    def delete_list_of_creatures_upon_death(self, lst_del) -> None:
        pass
        # todo using death index list to take from end colony objects array to fill out the "holes"
        #  another faster option, per death, use thread to take object from obj list end to insert it there,
        #  while running the regular functionality via threads usage

    def run_the_game(self):
        # while True:  # todo add user stop option (not a must), mm, or for now lets say 5 runs should be enough
        stop_after_x_cycles = 5
        while stop_after_x_cycles != 0:
            for ind_filled_objects in range(self.colony_current_num):
                # switch case run faster than inheritance (tested at run_time_check.py):
                match type(self.intrinsic_extrinsic[ind_filled_objects][0]).__name__:
                    # todo actually I can achieve the same behaviour (switch case here) without it(a little bit faster),
                    #  if func names are the same, and I would apply some more "if else" in each app,
                    #  it depends on functionality, assuming a real game would have more varied function per objects,
                    #  it seems correct to still use the switch case, and it doesnt cost that much time if used with
                    #  threads as well, as been tested in run_time_check, trying using all apps with 'Pass' per unneeded
                    #  func objects (e.g. crack with bee),
                    #  is worse than match case, and if objects really has and use exact same app names, it might work.
                    #  Prob is, E.g., 'crack' func goes only for eggs, hence,
                    #  this solution isn't good enough here instead of switch case.
                    #  Btw, optional is to change crack func name to "grow" as well, and truthfully,
                    #  I don't like it that much as it's not a real game/world solution IMO.

                    case "Egg":
                        additional_egg_growth = self.intrinsic_extrinsic[ind_filled_objects][0].cracking_shell(
                            self.intrinsic_extrinsic[ind_filled_objects][1].growth,  # update growth using current
                            self.intrinsic_factory,  # used if next stage achieved to change intrinsic
                            self.intrinsic_extrinsic,  # intrinsic extrinsic, for changing intrinsic type if needed,
                            # + get x,y from extrinsic
                            ind_filled_objects,  # object index in intrinsic extrinsic array
                            self.game_map  # update if needed
                        )
                        # (temperature irrelevant here, as eggs doesn't being laid in the winter).
                        self.intrinsic_extrinsic[ind_filled_objects][1].growth = additional_egg_growth
                    case "Larva":  # todo add temperature change event applying to growth, from .8-1.2 temp multi growth
                        additional_larva_growth = self.intrinsic_extrinsic[ind_filled_objects][0].growing_fast(
                            self.intrinsic_extrinsic[ind_filled_objects][1].growth,
                            self.intrinsic_factory,
                            self.intrinsic_extrinsic,  # intrinsic extrinsic, for changing intrinsic type if needed,
                            # + get x,y from extrinsic
                            ind_filled_objects,  # object index in intrinsic extrinsic array
                            self.game_map  # update if needed
                        )
                        self.intrinsic_extrinsic[ind_filled_objects][1].growth = additional_larva_growth
                    case "Pupa":  # todo add temperature change event applying to growth, from .8-1.2 temp multi growth.
                        additional_pupa_growth = self.intrinsic_extrinsic[ind_filled_objects][0].pupa_growth(
                            self.intrinsic_extrinsic[ind_filled_objects][1].growth,
                            self.intrinsic_factory,
                            self.intrinsic_extrinsic,  # intrinsic extrinsic, for changing intrinsic type if needed,
                            # + get x,y from extrinsic
                            ind_filled_objects,  # object index in intrinsic extrinsic array
                            self.game_map  # update if needed
                        )
                        self.intrinsic_extrinsic[ind_filled_objects][1].growth = additional_pupa_growth
                    case "Bee":  # todo so much more.
                        additional_bee_growth = self.intrinsic_extrinsic[ind_filled_objects][0].eat(
                            self.intrinsic_extrinsic[ind_filled_objects][1].growth,
                            self.intrinsic_extrinsic,  # intrinsic extrinsic, get x,y from extrinsic
                            ind_filled_objects,  # object index in intrinsic extrinsic array
                            self.game_map,
                            self.add_eggs_laid_by_queen  # if queen is big enough
                        )
                        self.intrinsic_extrinsic[ind_filled_objects][1].growth = additional_bee_growth
                    case _:
                        print("wrong naming! <(#_*)> check out what happened. (at run the game func)")
            stop_after_x_cycles -= 1
        print("End Game, Hope you enjoyed")

    def draw(self):
        pass
        # todo try implement using Tkinter
        # todo use here self.game_map or draw obj per objects move in threads, sounds better
        # currently_not_implemented, can be implemented using canvas, or pygame of some pixels


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
    health = np.random.uniform(low=0.1, high=10)  # todo higher chance to death the lower the health is
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
    ex_in_array = np.array([[0 for i in range(2)] for j in range(num_rows)], dtype=object)

    # map boundaries: assuming max colony num is 10000000, hence map would be 4000*4000, which is higher
    #                 than max num (10000000) sqrt... that way I get some "moving space" for sure.
    map_size = 4000  # height, width
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
    ans = ans.lower()
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
                ans = ans.lower()

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

    """ # Factory usage example:
    a = intrinsic_data_factory.get_class_instance("FQ", "Egg")  # Reusing existing class instance/creating new instance
    b = intrinsic_data_factory.get_class_instance("MQ", "Bee")  # Wrong type
    
    # showing all intrinsic "saved" classes in init:
    intrinsic_data_factory.list_classes()
    """

    # init game data, starting with creation of extrinsic data per intrinsic object
    intrinsic_extrinsic_arr, queens_coordinates, game_map = \
        create_init_intrinsic_and_extrinsic_data(intrinsic_data_factory,
                                                 bees_variation,
                                                 egg_num,
                                                 larva_num,
                                                 pupa_num,
                                                 bee_num,
                                                 colony_init_num)

    game = Bees_Game(intrinsic_extrinsic_arr, queens_coordinates, game_map, colony_init_num, intrinsic_data_factory)
    print("Starting the game")
    game.run_the_game()

    # todo add listener dp to temperature change...
    # todo add singleton to game class, and to factory class
    # todo death and birth while saving array filled without holes... and change colony objects counter
    # todo upon lay eggs event (new eggs),
    #  use bees counter id inside run the game app using game counter field and update it
    # todo add threads to make it all run much faster, e.g. thread per class at init, print aggregated printing data
    #  using thread instead of stopping prog for I/O etc
    # todo clean code, utility.py, classes.py shorten input at run the game app via func etc...
    # todo thread for queen bee movement with printing any object action it see after moving, and
    #  thread for all other colony objects functions and count printing types than print every (e.g.) 1 minute,
    #  run colony using some threads etc
    # todo part the data init creation func to smaller funcs each holding one distinct responsibility
    # todo make sure on queen kill all others queen by queen list, add check to not accidentally "kill" itself...
