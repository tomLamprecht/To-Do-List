import { Component, Input } from '@angular/core';
import { ListModel } from 'src/lib/data-access/models/listModel';
import { BackendService } from 'src/lib/feature/backend.service';

@Component({
  selector: 'board',
  templateUrl: './board.component.html',
  styleUrls: ['./board.component.scss'],
})

export class BoardComponent {

  constructor(private backendService: BackendService){}

  @Input()
  title = 'board';

  @Input()
  lists: ListModel[] = [];

  @Input()
  displayList:ListModel;

  @Input()
<<<<<<< HEAD
  flagCounter:number;

  @Input()
  todayCounter:number;

=======
  flagCounter:number = 5;

  @Input()
  todayCounter:number = 3;

  updateReady:boolean =true;
>>>>>>> e75614a3212424acd7b4e55e1bf3d92e51b9136b

  updateDisplayList(list:ListModel) {
    this.displayList=list;
    if(this.displayList.id == undefined)
      this.displayList = undefined;
    this.loseFocusOnDelay();
  }

  changeListTitle(event, list) {
    list.name = event;
    this.backendService.putList(list.id, list.name, list.position);
  }

  loseFocusOnDelay(){
    setTimeout(() => {this.loseFocus()} , 1)
  }

  loseFocus(){
    var tmp = document.createElement("input");
    document.body.appendChild(tmp);
    tmp.focus();
    document.body.removeChild(tmp);
  }

  ngAfterViewInit(){
    this.loseFocus();
    this.updateCounters();
  }

  updateCounters(){
    console.log("Updating...");
    setTimeout( () => {
      this.backendService.getFlagList().subscribe( (resp) => this.flagCounter = (resp.reminderItems == undefined) ? 0 : resp.reminderItems.length);
      this.backendService.getTodayList().subscribe( (resp) => this.todayCounter = (resp.reminderItems == undefined) ? 0 : resp.reminderItems.length);
      this.backendService.getLists().subscribe( (resp) => {this.lists = resp; this.loseFocusOnDelay() });
    }, 1)
  }

  onDeleteList(list){
    let index = this.lists.indexOf(list);
    this.lists.splice(index,1);
    if(this.displayList == list)
      this.displayList = undefined;

    this.backendService.deleteList(list.id);
    this.updateCounters();
  }

  createNewList(){
    this.backendService.postList("new List", this.lists.length).subscribe( (list) => this.lists.push(list));
  }

  ngOnInit(){
    console.log("starting...");
    this.backendService.getLists().subscribe( (resp) => {this.lists = resp; this.loseFocusOnDelay() });
  }

  flagClicked(){
    this.backendService.getFlagList().subscribe( (resp) => this.updateDisplayList(resp));
  }

<<<<<<< HEAD
  todayClicked(){
    this.backendService.getTodayList().subscribe( (resp) => this.updateDisplayList(resp));
=======
  changeListTitle(event, list) {
    list.name = event;
  }

  loseFocus(){
    var tmp = document.createElement("input");
    document.body.appendChild(tmp);
    tmp.focus();
    document.body.removeChild(tmp);
>>>>>>> e75614a3212424acd7b4e55e1bf3d92e51b9136b
  }

  ngAfterViewInit(){
    this.loseFocus();
  }

  updateCounters(){
    console.log("Updating...");
    //flagCounter = service.getFlagList.size();
    //todayCounter = service.getTodayList.size();

  }

  onDeleteList(list){
    let index = this.lists.indexOf(list);
    this.lists.splice(index,1);
    if(this.displayList == list)
      this.displayList = undefined;
  }


}
