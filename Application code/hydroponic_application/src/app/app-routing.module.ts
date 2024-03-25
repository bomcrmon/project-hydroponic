import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { LoginComponent } from './function/login/login.component';
import { RegisterComponent } from './function/register/register.component';
import { HomeComponent } from './function/home/home.component';
import { OutletComponent } from './outlet/outlet/outlet.component';

const routes: Routes = [
  // {path:'',redirectTo:'login',pathMatch:'full'},
  // {path:'outlet',component:OutletComponent},
  // {path:'login',component:LoginComponent},
  // {path:'register',component:RegisterComponent},
  // {path:'',component:HomeComponent},

  {
    path: '',
    component: OutletComponent,
    children: [
      {
        path: 'home',
        component: HomeComponent,
        data: {
          breadcrumbTh: 'ยืนยันคำสั่งซื้อ',
          breadcrumbEn: 'confirm-purchase',
        },
      },
    ],
  },
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule],
})
export class AppRoutingModule {}
