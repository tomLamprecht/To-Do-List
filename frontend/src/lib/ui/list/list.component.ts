import { Component, EventEmitter, Input, Output } from '@angular/core';
import { ReminderItemModel } from '../../data-access/models/reminderItemModel';

@Component({
  selector: 'list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.scss'],
})
export class ListComponent {
  @Input()
  title = 'list';

  @Input()
  idList: number;

  @Input()
  reminderItems: ReminderItemModel[];


  // addEmptyItem() {
  //   this.items.push({
  //     id: (Math.random() * 10000) | 0,
  //     title: 'empty',
  //     position: 0,
  //     timestamp: '',
  //   });
  // }

}
