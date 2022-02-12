import { Component, EventEmitter, Input, Output } from '@angular/core';
import { ListModel } from '../../data-access/models/listModel';

@Component({
  selector: 'listDisplayer',
  templateUrl: './listDisplayer.component.html',
  styleUrls: ['./listDisplayer.component.scss'],
})
export class ListDisplayerComponent {
  @Input()
  title = 'current List';

  @Input()
  displayList: ListModel;

  @Output()
  changeTitleEvent = new EventEmitter<string>();

  @Output()
  updateRequest = new EventEmitter();

  @Output()
  specialUpdateRequest = new EventEmitter();

  onChangeTitle(event) {
    this.changeTitleEvent.emit(event);
  }

  requestUpdate(id){
    this.updateRequest.emit()
    if( id == -1){
      this.specialUpdateRequest.emit();
    }
  }

  ngAfterViewInit(){
    this.loseFocus();
  }

  loseFocus(){
    var tmp = document.createElement("input");
    document.body.appendChild(tmp);
    tmp.focus();
    document.body.removeChild(tmp);
  }

}
