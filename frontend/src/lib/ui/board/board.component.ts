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
  flagCounter:number;

  @Input()
  todayCounter:number;


  updateDisplayList(list:ListModel) {
    this.displayList=list;
    if(this.displayList.id == undefined)
      this.displayList = undefined;
    this.loseFocusOnDelay();
  }

  changeListTitle(event, list) {
    list.name = event;
    this.backendService.putList(list.id, list.name).subscribe( (resp) => {});
  }

  loseFocusOnDelay(){
    setTimeout(() => {this.loseFocus()} , 20)
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
      this.backendService.getFlagList().subscribe( (resp) => this.flagCounter = (resp.reminderItems == undefined) ? 0 : resp.reminderItems.length);
      this.backendService.getTodayList().subscribe( (resp) => this.todayCounter = (resp.reminderItems == undefined) ? 0 : resp.reminderItems.length);
  }

  updateLists(){
    this.backendService.getLists().subscribe( (resp) => {this.lists = resp; this.loseFocusOnDelay() });
  }

  onDeleteList(list){
    let index = this.lists.indexOf(list);
    this.lists.splice(index,1);
    if(this.displayList == list)
      this.displayList = undefined;

    this.backendService.deleteList(list.id).subscribe( (resp) => {this.updateCounters()});
  }

  createNewList(){
    this.backendService.postList("").subscribe( (list) => this.lists.push(list));
  }

  ngOnInit(){
    this.backendService.getLists().subscribe( (resp) => {this.lists = resp; this.loseFocusOnDelay() });
  }

  flagClicked(){
    this.backendService.getFlagList().subscribe( (resp) => this.updateDisplayList(resp));
  }

  todayClicked(){
    this.backendService.getTodayList().subscribe( (resp) => this.updateDisplayList(resp));
  }

}
