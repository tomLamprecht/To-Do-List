import { Component, Input } from '@angular/core';
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



  //@Input()
  // lists: ListModel[] = [
  //   {
  //     id: 0,
  //     name: 'to do',
  //     position: 0,
  //     reminderItems: [
  //       {
  //         id: 0,
  //         title: 'first task',
  //         position: 0,
  //         timestamp: '2021-12-09T10:04:42.058Z',
  //         flag: false,
  //       },
  //       {
  //         id: 1,
  //         title: 'second task',
  //         position: 1,
  //         timestamp: '2021-12-09T10:04:42.058Z',
  //         flag: false,
  //       },
  //       {
  //         id: 2,
  //         title: 'third task',
  //         position: 2,
  //         timestamp: '2021-12-09T10:04:42.058Z',
  //         flag: false,
  //       },
  //     ],
  //   },

  //   {
  //     id: 1,
  //     name: 'doing',
  //     position: 1,
  //     reminderItems: [
  //       {
  //         id: 3,
  //         title: 'my special first task',
  //         position: 0,
  //         timestamp: '2021-12-09T10:04:42.058Z',
  //         flag: false,
  //       },
  //     ],
  //   },

  //   // {
  //   //   id: 2,
  //   //   name: 'done',
  //   //   position: 2,
  //   //   reminderItems: [
  //   //     {
  //   //       id: 4,
  //   //       title: 'first task',
  //   //       position: 0,
  //   //       timestamp: '2021-12-09T10:04:42.058Z',
  //   //       flag: false,
  //   //     },
  //   //     {
  //   //       id: 5,
  //   //       title: 'second task',
  //   //       position: 1,
  //   //       timestamp: '2021-12-09T10:04:42.058Z',
  //   //       flag: false,
  //   //     },
  //   //   ],
  //   // },
  // ];


}
