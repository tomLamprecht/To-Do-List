import { Component, EventEmitter, Input, Output } from '@angular/core';
import { ListModel } from 'src/lib/data-access/models/listModel';

@Component({
  selector: 'listHeader',
  templateUrl: './listHeader.component.html',
  styleUrls: ['./listHeader.component.scss'],
})
export class ListHeaderComponent {
  @Input()
  title = 'listHeader';

   @Input()
   list: ListModel;

   @Output()
   onDisplay = new EventEmitter<ListModel>();

   emitOnDisplay() {
     this.onDisplay.emit(this.list);
   }

}
